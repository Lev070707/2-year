#include "min_max.h"
#include "console_mutex.h"
#include <windows.h>
#include <cstdio>

int find_min_nonthread(const int* arr, int n) {
    if (n <= 0) return 0;
    int minv = arr[0];
    for (int i = 1; i < n; ++i) if (arr[i] < minv) minv = arr[i];
    return minv;
}

int find_max_nonthread(const int* arr, int n) {
    if (n <= 0) return 0;
    int maxv = arr[0];
    for (int i = 1; i < n; ++i) if (arr[i] > maxv) maxv = arr[i];
    return maxv;
}

DWORD WINAPI min_max_thread(LPVOID lpParam) {
    MinMaxParams* p = (MinMaxParams*)lpParam;
    if (!p || p->n <= 0) { if (p && p->doneEvent) SetEvent(p->doneEvent); return 0; }
    int minv = p->arr[0];
    int maxv = p->arr[0];
    for (int i = 1; i < p->n; ++i) {
        if (p->arr[i] < minv) minv = p->arr[i];
        Sleep(7);
        if (p->arr[i] > maxv) maxv = p->arr[i];
        Sleep(7);
    }
    p->minVal = minv;
    p->maxVal = maxv;

    char buf[128];
    _snprintf(buf, sizeof(buf), "Min: %d\n", minv);
    console_printf(buf);
    _snprintf(buf, sizeof(buf), "Max: %d\n", maxv);
    console_printf(buf);

    if (p->doneEvent) SetEvent(p->doneEvent);
    return 0;
}
