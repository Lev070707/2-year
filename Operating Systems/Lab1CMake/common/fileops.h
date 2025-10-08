#pragma once
#include <string>
#include <vector>
#include "employee.h"

bool writeEmployees(const std::string& filename, const std::vector<employee>& emps, std::string& errorMsg);
bool readEmployees(const std::string& filename, std::vector<employee>& emps, std::string& errorMsg);