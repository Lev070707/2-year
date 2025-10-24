#define BOOST_TEST_MODULE Lab3Tests
#include <boost/test/included/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <windows.h>
#include "SharedArray.h"
#include "Marker.h"

BOOST_AUTO_TEST_CASE(shared_array_basic) {
    SharedArray arr(5);
    BOOST_CHECK_EQUAL(arr.size(), 5u);

    arr.set(0, 10);
    BOOST_CHECK_EQUAL(arr.get(0), 10);

    arr.clearMarks(10);
    BOOST_CHECK_EQUAL(arr.get(0), 10);
}

BOOST_AUTO_TEST_CASE(marker_lifecycle_basic) {
    SharedArray arr(10);
    SyncPrimitives sync;
    MarkerParams* p = new MarkerParams();
    p->id = 1;
    p->array = &arr;
    p->sync = &sync;
    p->terminateEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
    EnterCriticalSection(&sync.cs);
    sync.activeMarkers++;
    LeaveCriticalSection(&sync.cs);

    HANDLE h = CreateThread(NULL, 0, MarkerThreadProc, p, 0, &p->threadId);
    BOOST_REQUIRE_MESSAGE(h != NULL, "CreateThread failed");

    SetEvent(sync.startEvent);

    Sleep(100);

    SetEvent(p->terminateEvent);
    WaitForSingleObject(h, INFINITE);
    CloseHandle(h);
    CloseHandle(p->terminateEvent);
    delete p;

    BOOST_CHECK_EQUAL(arr.size(), 10u);
}
