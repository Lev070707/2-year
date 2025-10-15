#pragma once
#include <windows.h>

double compute_average_nonthread(const int* arr, int n);

struct AverageParams {
    int* arr;
    int n;
    double avg;
    HANDLE doneEvent;
};

DWORD WINAPI average_thread(LPVOID lpParam);