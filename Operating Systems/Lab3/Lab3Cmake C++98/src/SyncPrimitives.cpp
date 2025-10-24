#include "SyncPrimitives.h"
#include "Utils.h"
#include <stdexcept>

SyncPrimitives::SyncPrimitives() : startEvent(NULL), continueEvent(NULL), allSignaledEvent(NULL),
impossibleCount(0), activeMarkers(0)
{
    InitializeCriticalSection(&cs);
    startEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
    if (!startEvent) throw std::runtime_error(std::string("CreateEvent(startEvent) failed: ") + LastErrorMessage());
    continueEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
    if (!continueEvent) throw std::runtime_error(std::string("CreateEvent(continueEvent) failed: ") + LastErrorMessage());
    allSignaledEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
    if (!allSignaledEvent) throw std::runtime_error(std::string("CreateEvent(allSignaledEvent) failed: ") + LastErrorMessage());
}

SyncPrimitives::~SyncPrimitives() {
    if (startEvent) CloseHandle(startEvent);
    if (continueEvent) CloseHandle(continueEvent);
    if (allSignaledEvent) CloseHandle(allSignaledEvent);
    DeleteCriticalSection(&cs);
}