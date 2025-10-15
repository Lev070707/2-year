#pragma once
#include <windows.h>
#include <cstdio>

extern HANDLE gConsoleMutex;

inline void console_printf(const char* msg) {
    if (gConsoleMutex) {
        WaitForSingleObject(gConsoleMutex, INFINITE);
        fputs(msg, stdout);
        fflush(stdout);
        ReleaseMutex(gConsoleMutex);
    }
    else {
        fputs(msg, stdout);
        fflush(stdout);
    }
}