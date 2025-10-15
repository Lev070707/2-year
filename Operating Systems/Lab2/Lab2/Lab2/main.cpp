// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <limits>
#include <cmath>

#include "min_max.h"
#include "average.h"

std::mutex console_mutex;

int main() {
    try {
        std::cout << "Enter array size: ";
        int n;
        if (!(std::cin >> n)) {
            throw std::runtime_error("Invalid input for array size");
        }
        if (n <= 0) {
            throw std::runtime_error("Array size must be positive");
        }

        std::vector<int> arr;
        arr.reserve(n);
        std::cout << "Enter " << n << " integer elements (separated by spaces or newlines):\n";
        for (int i = 0; i < n; ++i) {
            int v;
            if (!(std::cin >> v)) {
                throw std::runtime_error("Invalid input for array element");
            }
            arr.push_back(v);
        }

        std::thread t_minmax, t_avg;
        try {
            t_minmax = std::thread(minMaxThread, std::cref(arr));
            t_avg = std::thread(averageThread, std::cref(arr));
        }
        catch (...) {
            if (t_minmax.joinable()) t_minmax.join();
            if (t_avg.joinable()) t_avg.join();
            throw;
        }

        if (t_minmax.joinable()) t_minmax.join();
        if (t_avg.joinable())    t_avg.join();

        if (arr.empty()) {
            std::lock_guard<std::mutex> lk(console_mutex);
            std::cout << "Main: array empty after threads.\n";
            return 0;
        }

        int minVal = std::numeric_limits<int>::max();
        int maxVal = std::numeric_limits<int>::min();
        long long sum = 0;
        for (int x : arr) {
            if (x < minVal) minVal = x;
            if (x > maxVal) maxVal = x;
            sum += x;
        }
        double avg = static_cast<double>(sum) / static_cast<double>(arr.size());
        int avgInt = static_cast<int>(std::round(avg));

        {
            std::lock_guard<std::mutex> lk(console_mutex);
            std::cout << "Main: replacing min (" << minVal << ") and max (" << maxVal << ") with average (" << avgInt << ")\n";
        }

        for (auto& x : arr) {
            if (x == minVal || x == maxVal) {
                x = avgInt;
            }
        }

        {
            std::lock_guard<std::mutex> lk(console_mutex);
            std::cout << "Resulting array:\n";
            for (size_t i = 0; i < arr.size(); ++i) {
                std::cout << arr[i] << (i + 1 == arr.size() ? "\n" : " ");
            }
        }
    }
    catch (const std::exception& ex) {
        std::lock_guard<std::mutex> lk(console_mutex);
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
