#pragma once
#include <windows.h>

int find_min_nonthread(const int* arr, int n);
int find_max_nonthread(const int* arr, int n);

struct MinMaxParams {
    int* arr;
    int n;
    int minVal;
    int maxVal;
    HANDLE doneEvent;
};

DWORD WINAPI min_max_thread(LPVOID lpParam);