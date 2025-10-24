#pragma once
#include <windows.h>

struct SyncPrimitives {
    CRITICAL_SECTION cs;
    HANDLE startEvent;
    HANDLE continueEvent;
    HANDLE allSignaledEvent;
    int impossibleCount;
    int activeMarkers;

    SyncPrimitives();
    ~SyncPrimitives();
};