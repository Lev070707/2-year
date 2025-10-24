#include "SharedArray.h"
#include <stdexcept>
#include <algorithm>
#include <cstring>

SharedArray::SharedArray(size_t n) : data_(NULL), n_(n) {
    if (n_ == 0) throw std::invalid_argument("array size must be >0");
    data_ = (int*)malloc(sizeof(int) * n_);
    if (!data_) throw std::bad_alloc();
    memset(data_, 0, sizeof(int) * n_);
}
SharedArray::~SharedArray() {
    if (data_) free(data_);
    data_ = NULL;
}
int SharedArray::get(size_t idx) {
    if (idx >= n_) throw std::out_of_range("index");
    return data_[idx];
}
void SharedArray::set(size_t idx, int value) {
    if (idx >= n_) throw std::out_of_range("index");
    data_[idx] = value;
}
size_t SharedArray::size() const { return n_; }

void SharedArray::clearMarks(int markerId) {
    for (size_t i = 0;i < n_;++i) {
        if (data_[i] == markerId) data_[i] = 0;
    }
}

std::vector<int> SharedArray::snapshot() {
    std::vector<int> v;
    v.reserve(n_);
    for (size_t i = 0;i < n_;++i) v.push_back(data_[i]);
    return v;
}
