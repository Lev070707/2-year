#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "SharedArray.h"
#include "SyncPrimitives.h"
#include "Marker.h"
#include "Utils.h"

int main() {
    try {
        std::cout << "Enter array size: ";
        size_t n;
        if (!(std::cin >> n)) { std::cerr << "Invalid size\n"; return 1; }
        SharedArray arr(n);

        std::cout << "Enter number of marker threads: ";
        int m;
        if (!(std::cin >> m) || m <= 0) { std::cerr << "Invalid count\n"; return 1; }

        SyncPrimitives sync;
        std::vector<MarkerParams*> markers;
        markers.reserve(m);

        for (int i = 1;i <= m;++i) {
            MarkerParams* p = new MarkerParams();
            p->id = i;
            p->array = &arr;
            p->sync = &sync;
            p->terminateEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
            if (!p->terminateEvent) throw std::runtime_error(std::string("CreateEvent failed: ") + LastErrorMessage());
            EnterCriticalSection(&sync.cs);
            sync.activeMarkers++;
            LeaveCriticalSection(&sync.cs);

            HANDLE h = CreateThread(NULL, 0, MarkerThreadProc, p, 0, &p->threadId);
            if (!h) throw std::runtime_error(std::string("CreateThread failed: ") + LastErrorMessage());
            p->threadHandle = h;
            markers.push_back(p);
        }

        SetEvent(sync.startEvent);

        while (true) {
            WaitForSingleObject(sync.allSignaledEvent, INFINITE);

            EnterCriticalSection(&sync.cs);
            std::vector<int> snap = arr.snapshot();
            LeaveCriticalSection(&sync.cs);

            std::cout << "Array: ";
            for (size_t i = 0;i < snap.size();++i) std::cout << snap[i] << ' ';
            std::cout << '\n';

            std::cout << "Active markers:\n";
            for (size_t i = 0;i < markers.size();++i) {
                if (markers[i]) std::cout << "  " << markers[i]->id << '\n';
            }

            int toTerminate = -1;
            std::cout << "Enter marker id to terminate (or 0 to quit): ";
            if (!(std::cin >> toTerminate)) { std::cerr << "Invalid input\n"; break; }
            if (toTerminate == 0) {
                for (size_t i = 0;i < markers.size();++i) {
                    if (markers[i]) SetEvent(markers[i]->terminateEvent);
                }
                break;
            }

            MarkerParams* chosen = NULL;
            for (size_t i = 0;i < markers.size();++i) {
                if (markers[i] && markers[i]->id == toTerminate) { chosen = markers[i]; break; }
            }
            if (!chosen) {
                std::cout << "No such active marker\n";
                EnterCriticalSection(&sync.cs);
                sync.impossibleCount = 0;
                ResetEvent(sync.allSignaledEvent);
                SetEvent(sync.continueEvent);
                Sleep(10);
                ResetEvent(sync.continueEvent);
                continue;
            }

            SetEvent(chosen->terminateEvent);
            WaitForSingleObject(chosen->threadHandle, INFINITE);
            CloseHandle(chosen->threadHandle);
            CloseHandle(chosen->terminateEvent);

            for (size_t i = 0;i < markers.size();++i) {
                if (markers[i] && markers[i]->id == toTerminate) {
                    delete markers[i];
                    markers[i] = NULL;
                    break;
                }
            }

            EnterCriticalSection(&sync.cs);
            sync.activeMarkers--;
            sync.impossibleCount = 0;
            LeaveCriticalSection(&sync.cs);
            ResetEvent(sync.allSignaledEvent);

            EnterCriticalSection(&sync.cs);
            snap = arr.snapshot();
            LeaveCriticalSection(&sync.cs);
            std::cout << "Array after termination: ";
            for (size_t i = 0;i < snap.size();++i) std::cout << snap[i] << ' ';
            std::cout << '\n';

            SetEvent(sync.continueEvent);
            Sleep(10);
            ResetEvent(sync.continueEvent);

            bool any = false;
            for (size_t i = 0;i < markers.size();++i) if (markers[i]) { any = true; break; }
            if (!any) break;
        }

        for (size_t i = 0;i < markers.size();++i) {
            if (markers[i]) {
                SetEvent(markers[i]->terminateEvent);
                WaitForSingleObject(markers[i]->threadHandle, INFINITE);
                CloseHandle(markers[i]->threadHandle);
                CloseHandle(markers[i]->terminateEvent);
                delete markers[i];
            }
        }

        std::cout << "All markers finished. Exiting.\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}