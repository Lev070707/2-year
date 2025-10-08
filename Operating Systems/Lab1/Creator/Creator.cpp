#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "fileops.h"
#include "employee.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: Creator <binary_filename> <record_count>\n";
        return 1;
    }
    std::string filename = argv[1];
    int count = 0;
    try { count = std::stoi(argv[2]); }
    catch (...) { std::cerr << "Invalid record count\n"; return 1; }
    if (count <= 0) { std::cerr << "Record count must be positive\n"; return 1; }

    std::vector<employee> emps; emps.reserve(count);
    for (int i = 0; i < count; ++i) {
        employee e{};
        std::string name;
        std::cout << "Enter ID Name Hours: ";
        if (!(std::cin >> e.num >> name >> e.hours)) { std::cerr << "Invalid input. Expected: <int> <string> <double>\n"; return 1; }
        std::strncpy(e.name, name.c_str(), sizeof(e.name) - 1);
        e.name[sizeof(e.name) - 1] = '\\0';
        emps.push_back(e);
    }
    std::string err;
    if (!writeEmployees(filename, emps, err)) { std::cerr << "Error: " << err << "\n"; return 1; }
    return 0;
}
