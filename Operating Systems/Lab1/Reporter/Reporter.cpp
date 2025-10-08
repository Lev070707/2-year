#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include "fileops.h"
#include "employee.h"

int main(int argc, char** argv) {
    if (argc != 4) { std::cerr << "Usage: Reporter <source_binary> <report_file> <hour_rate>\n"; return 1; }
    std::string src = argv[1], rpt = argv[2];
    double rate = 0.0;
    try { rate = std::stod(argv[3]); }
    catch (...) { std::cerr << "Invalid hour rate\n"; return 1; }

    std::vector<employee> emps;
    std::string err;
    if (!readEmployees(src, emps, err)) { std::cerr << "Error: " << err << "\n"; return 1; }

    std::sort(emps.begin(), emps.end(), [](const employee& a, const employee& b) { return a.num < b.num; });

    std::ofstream ofs(rpt);
    if (!ofs.is_open()) { std::cerr << "Cannot open report file for writing: " << rpt << "\n"; return 1; }

    ofs << "Report for file: " << src << "\n";
    ofs << "ID\tName\tHours\tSalary\n";
    ofs << std::fixed << std::setprecision(2);
    for (const auto& e : emps) {
        double salary = e.hours * rate;
        ofs << e.num << "\t" << e.name << "\t" << e.hours << "\t" << salary << "\n";
    }
    return 0;
}

