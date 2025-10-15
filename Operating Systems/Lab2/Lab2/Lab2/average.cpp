#include "average.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <sstream>
#include <iomanip>

extern std::mutex console_mutex;

void averageThread(const std::vector<int>& arr) {
    if (arr.empty()) {
        std::lock_guard<std::mutex> lk(console_mutex);
        std::cout << "average: array is empty\n";
        return;
    }

    long long sum = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        sum += arr[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(12));
    }
    double avg = static_cast<double>(sum) / static_cast<double>(arr.size());

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4) << avg;

    {
        std::lock_guard<std::mutex> lk(console_mutex);
        std::cout << "average: Average = " << oss.str() << "\n";
    }
}