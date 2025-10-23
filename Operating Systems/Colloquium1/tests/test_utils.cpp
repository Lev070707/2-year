#include "gtest/gtest.h"
#include "utils.h"
#include <vector>

TEST(FactorialsTest, SmallN) {
    auto v = compute_factorials(5);
    std::vector<unsigned long long> expect = { 1ULL, 2ULL, 6ULL, 24ULL, 120ULL };
    EXPECT_EQ(v, expect);
}

TEST(FactorialsTest, ZeroN) {
    auto v = compute_factorials(0);
    EXPECT_TRUE(v.empty());
}

TEST(FactorialsTest, OverflowStop) {
    auto v = compute_factorials(100);
    EXPECT_GE(v.size(), 1u);
    unsigned long long last = v.back();
    unsigned long long nextIndex = static_cast<unsigned long long>(v.size()) + 1ULL;
    EXPECT_TRUE(last > 0);
    EXPECT_TRUE(last > std::numeric_limits<unsigned long long>::max() / nextIndex
        || v.size() == static_cast<size_t>(100));
}

TEST(RemoveDupTest, Basic) {
    std::vector<long long> a = { 1,2,2,3,1,4 };
    auto out = remove_duplicates(a);
    std::vector<long long> expect = { 1,2,3,4 };
    EXPECT_EQ(out, expect);
}

TEST(LinkedListRevTest, Empty) {
    Node* h = nullptr;
    Node* r = rev(h);
    EXPECT_EQ(r, nullptr);
}

TEST(LinkedListRevTest, Single) {
    Node* h = make_list_from_vector({ 42 });
    Node* r = rev(h);
    auto v = to_vector(r);
    EXPECT_EQ(v.size(), 1u);
    EXPECT_EQ(v[0], 42);
    free_list(r);
}

TEST(LinkedListRevTest, Multiple) {
    std::vector<int> in = { 1,2,3,4,5 };
    Node* h = make_list_from_vector(in);
    Node* r = rev(h);
    auto v = to_vector(r);
    std::vector<int> expect = { 5,4,3,2,1 };
    EXPECT_EQ(v, expect);
    free_list(r);
}
