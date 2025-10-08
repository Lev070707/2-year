#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "fileops.h"
#include "employee.h"

static bool LaunchProcessAndWait(const std::string& cmdline, DWORD& exitCode, std::string& err) {
    STARTUPINFOA si; PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si)); si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    std::vector<char> cmd(cmdline.begin(), cmdline.end()); cmd.push_back('\0');
    if (!CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        err = "CreateProcess failed, code=" + std::to_string(GetLastError()); return false;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) { err = "GetExitCodeProcess failed, code=" + std::to_string(GetLastError()); CloseHandle(pi.hProcess); CloseHandle(pi.hThread); return false; }
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    return true;
}

int main() {
    std::string binfile; int count = 0;
    std::cout << "Enter binary filename and record count: ";
    if (!(std::cin >> binfile >> count)) { std::cerr << "Invalid input\n"; return 1; }

    std::stringstream sc; sc << "Creator.exe \"" << binfile << "\" " << count;
    DWORD code = 0; std::string err;
    if (!LaunchProcessAndWait(sc.str(), code, err)) { std::cerr << "Failed to launch Creator: " << err << "\n"; return 1; }
    if (code != 0) { std::cerr << "Creator exited with code " << code << "\n"; return 1; }

    std::vector<employee> emps;
    if (!readEmployees(binfile, emps, err)) { std::cerr << "Error reading binary file: " << err << "\n"; return 1; }
    std::cout << "Binary file contents:\n";
    for (const auto& e : emps) std::cout << "ID=" << e.num << " Name=" << e.name << " Hours=" << e.hours << "\n";

    std::string rptfile; double rate = 0.0;
    std::cout << "Enter report filename and pay rate: ";
    if (!(std::cin >> rptfile >> rate)) { std::cerr << "Invalid input\n"; return 1; }

    std::stringstream sr; sr << "Reporter.exe \"" << binfile << "\" \"" << rptfile << "\" " << rate;
    if (!LaunchProcessAndWait(sr.str(), code, err)) { std::cerr << "Failed to launch Reporter: " << err << "\n"; return 1; }
    if (code != 0) { std::cerr << "Reporter exited with code " << code << "\n"; return 1; }

    std::ifstream ifs(rptfile);
    if (!ifs.is_open()) { std::cerr << "Cannot open report file: " << rptfile << "\n"; return 1; }
    std::cout << "Report contents:\n";
    std::string line;
    while (std::getline(ifs, line)) std::cout << line << "\n";
    return 0;
}