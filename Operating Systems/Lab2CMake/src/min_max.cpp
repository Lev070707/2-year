#include "min_max.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

extern std::mutex console_mutex;

void minMaxThread(const std::vector<int>& arr) {
    if (arr.empty()) {
        std::lock_guard<std::mutex> lk(console_mutex);
        std::cout << "min_max: array is empty\n";
        return;
    }

    int minVal = arr[0];
    int maxVal = arr[0];

    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(7));

        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(7));
    }

    {
        std::lock_guard<std::mutex> lk(console_mutex);
        std::cout << "min_max: Min = " << minVal << "\n";
        std::cout << "min_max: Max = " << maxVal << "\n";
    }
}