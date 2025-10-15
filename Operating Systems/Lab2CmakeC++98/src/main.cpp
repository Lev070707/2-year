#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "min_max.h"
#include "average.h"
#include "console_mutex.h"

int main() {
    gConsoleMutex = CreateMutex(NULL, FALSE, NULL);

    std::cout << "Enter number of elements: ";
    int n; if (!(std::cin >> n)) return 1; if (n <= 0) return 1;
    std::vector<int> arr; arr.reserve(n);
    for (int i = 0; i < n; ++i) { int x; std::cin >> x; arr.push_back(x); }

    MinMaxParams mm; mm.arr = &arr[0]; mm.n = n; mm.minVal = 0; mm.maxVal = 0; mm.doneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    AverageParams ap; ap.arr = &arr[0]; ap.n = n; ap.avg = 0.0; ap.doneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    HANDLE hMin = CreateThread(NULL, 0, min_max_thread, &mm, 0, NULL);
    HANDLE hAvg = CreateThread(NULL, 0, average_thread, &ap, 0, NULL);

    HANDLE events[2]; events[0] = mm.doneEvent; events[1] = ap.doneEvent;
    WaitForMultipleObjects(2, events, TRUE, INFINITE);

    int avgInt = (int)round(ap.avg);
    for (int i = 0; i < n; ++i) if (arr[i] == mm.minVal || arr[i] == mm.maxVal) arr[i] = avgInt;

    std::cout << "Resulting array:\n";
    for (int i = 0; i < n; ++i) std::cout << arr[i] << (i + 1 == n ? "\n" : " ");

    CloseHandle(mm.doneEvent); CloseHandle(ap.doneEvent);
    if (hMin) CloseHandle(hMin); if (hAvg) CloseHandle(hAvg);
    if (gConsoleMutex) { CloseHandle(gConsoleMutex); gConsoleMutex = NULL; }
    return 0;
}