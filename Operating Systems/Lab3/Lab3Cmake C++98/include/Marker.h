#pragma once
#include <windows.h>
#include "SharedArray.h"
#include "SyncPrimitives.h"

struct MarkerParams {
    int id;
    SharedArray* array;
    SyncPrimitives* sync;
    HANDLE terminateEvent;
    HANDLE threadHandle;
    DWORD threadId;
    int markedCount;
    MarkerParams() : terminateEvent(NULL), threadHandle(NULL), threadId(0), markedCount(0) {}
};

DWORD WINAPI MarkerThreadProc(LPVOID lpParam);