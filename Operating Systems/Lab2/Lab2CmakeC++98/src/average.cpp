#include "average.h"
#include "console_mutex.h"
#include <windows.h>
#include <cstdio>

double compute_average_nonthread(const int* arr, int n) {
    if (n <= 0) return 0.0;
    long long sum = 0;
    for (int i = 0; i < n; ++i) sum += arr[i];
    return (double)sum / (double)n;
}

DWORD WINAPI average_thread(LPVOID lpParam) {
    AverageParams* p = (AverageParams*)lpParam;
    if (!p || p->n <= 0) { if (p && p->doneEvent) SetEvent(p->doneEvent); return 0; }
    long long sum = 0;
    for (int i = 0; i < p->n; ++i) {
        sum += p->arr[i];
        Sleep(12);
    }
    p->avg = (double)sum / (double)p->n;

    char buf[128];
    _snprintf(buf, sizeof(buf), "Average: %.4f\n", p->avg);
    console_printf(buf);

    if (p->doneEvent) SetEvent(p->doneEvent);
    return 0;
}