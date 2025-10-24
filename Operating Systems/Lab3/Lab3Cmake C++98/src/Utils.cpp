#include "Utils.h"
#include <windows.h>
#include <sstream>

std::string LastErrorMessage(unsigned long err) {
    if (err == 0) err = GetLastError();
    if (err == 0) return std::string("(no error)");
    LPVOID msgBuf = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        err,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&msgBuf),
        0, NULL);
    std::string s = msgBuf ? static_cast<const char*>(msgBuf) : std::string("(unknown)");
    if (msgBuf) LocalFree(msgBuf);
    return s;
}