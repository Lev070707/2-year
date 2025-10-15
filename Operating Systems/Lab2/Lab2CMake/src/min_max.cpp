#include "min_max.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

extern std::mutex console_mutex;

int find_min(const std::vector<int>& arr) {
    int min_val = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(7));
        if (arr[i] < min_val)
            min_val = arr[i];
    }
    return min_val;
}

int find_max(const std::vector<int>& arr) {
    int max_val = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(7));
        if (arr[i] > max_val)
            max_val = arr[i];
    }
    return max_val;
}

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