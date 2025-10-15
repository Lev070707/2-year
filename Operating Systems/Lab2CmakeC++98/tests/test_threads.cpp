#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "min_max.h"
#include "average.h"
#include <windows.h>

TEST_CASE("compute_average_nonthread") {
    int arr[] = { 1,2,3,4,5 };
    double avg = compute_average_nonthread(arr, 5);
    CHECK_EQ(avg, 3.0);
}

TEST_CASE("find_min_max_nonthread") {
    int arr[] = { 5,1,9,3 };
    CHECK_EQ(find_min_nonthread(arr, 4), 1);
    CHECK_EQ(find_max_nonthread(arr, 4), 9);
}

TEST_CASE("threads_set_values") {
    int arr[] = { 2,4,6 };
    AverageParams ap; ap.arr = arr; ap.n = 3; ap.avg = 0.0; ap.doneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    HANDLE h = CreateThread(NULL, 0, average_thread, &ap, 0, NULL);
    WaitForSingleObject(ap.doneEvent, INFINITE);
    CloseHandle(ap.doneEvent);
    if (h) CloseHandle(h);
    CHECK_EQ(ap.avg, 4.0);

    int arr2[] = { 7,2,8,2,10 };
    MinMaxParams mp; mp.arr = arr2; mp.n = 5; mp.minVal = 0; mp.maxVal = 0; mp.doneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    HANDLE h2 = CreateThread(NULL, 0, min_max_thread, &mp, 0, NULL);
    WaitForSingleObject(mp.doneEvent, INFINITE);
    CloseHandle(mp.doneEvent);
    if (h2) CloseHandle(h2);
    CHECK_EQ(mp.minVal, 2);
    CHECK_EQ(mp.maxVal, 10);
}
