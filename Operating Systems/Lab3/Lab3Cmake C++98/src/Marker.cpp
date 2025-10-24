#include "Marker.h"
#include "Utils.h"
#include <cstdlib>
#include <cstdio>

static void SignalImpossible(SyncPrimitives* sync) {
    EnterCriticalSection(&sync->cs);
    sync->impossibleCount++;
    if (sync->impossibleCount >= sync->activeMarkers) {
        SetEvent(sync->allSignaledEvent);
    }
    LeaveCriticalSection(&sync->cs);
}

DWORD WINAPI MarkerThreadProc(LPVOID lpParam) {
    MarkerParams* p = (MarkerParams*)lpParam;
    if (!p) return 1;
    try {
        DWORD w = WaitForSingleObject(p->sync->startEvent, INFINITE);
        if (w != WAIT_OBJECT_0) {
            return 1;
        }
        srand(p->id);

        while (true) {
            int r = rand();
            size_t idx = (size_t)(r % (int)p->array->size());

            EnterCriticalSection(&p->sync->cs);
            int val = p->array->get(idx);
            if (val == 0) {
                LeaveCriticalSection(&p->sync->cs);
                Sleep(5);
                EnterCriticalSection(&p->sync->cs);
                p->array->set(idx, p->id);
                p->markedCount++;
                LeaveCriticalSection(&p->sync->cs);
                Sleep(5);
                continue;
            }
            else {
                printf("Marker %d: marked=%d, blocked_idx=%u\n", p->id, p->markedCount, (unsigned)idx);
                SignalImpossible(p->sync);
                LeaveCriticalSection(&p->sync->cs);

                HANDLE handles[2];
                handles[0] = p->terminateEvent;
                handles[1] = p->sync->continueEvent;
                DWORD res = WaitForMultipleObjects(2, handles, FALSE, INFINITE);
                if (res == WAIT_OBJECT_0) {
                    EnterCriticalSection(&p->sync->cs);
                    p->array->clearMarks(p->id);
                    LeaveCriticalSection(&p->sync->cs);
                    break;
                }
                else if (res == WAIT_OBJECT_0 + 1) {
                    continue;
                }
                else {
                    break;
                }
            }
        }
    }
    catch (...) {
        return 1;
    }
    return 0;
}