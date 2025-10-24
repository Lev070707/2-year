#pragma once
#include <vector>
#include <windows.h>

class SharedArray {
public:
    SharedArray(size_t n);
    ~SharedArray();
    int get(size_t idx);
    void set(size_t idx, int value);
    size_t size() const;
    void clearMarks(int markerId);
    std::vector<int> snapshot();

private:
    int* data_;
    size_t n_;
};