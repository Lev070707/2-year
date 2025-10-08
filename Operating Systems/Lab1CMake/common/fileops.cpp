#include "fileops.h"
#include <fstream>
#include <cstring>

bool writeEmployees(const std::string& filename, const std::vector<employee>& emps, std::string& errorMsg) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs.is_open()) {
        errorMsg = "Cannot open file for writing: " + filename;
        return false;
    }
    for (const auto& e : emps) {
        ofs.write(reinterpret_cast<const char*>(&e), sizeof(e));
        if (!ofs) {
            errorMsg = "Write error to file: " + filename;
            return false;
        }
    }
    return true;
}

bool readEmployees(const std::string& filename, std::vector<employee>& emps, std::string& errorMsg) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open()) {
        errorMsg = "Cannot open file for reading: " + filename;
        return false;
    }
    emps.clear();
    employee e;
    while (ifs.read(reinterpret_cast<char*>(&e), sizeof(e))) {
        emps.push_back(e);
    }
    if (ifs.bad()) {
        errorMsg = "Read error from file: " + filename;
        return false;
    }
    return true;
}
