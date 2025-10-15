#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include "average.h"
#include "min_max.h"

std::mutex console_mutex;

TEST_CASE("find_min returns correct minimum") {
    std::vector<int> v = { 5, 2, 8, -3, 7 };
    CHECK(find_min(v) == -3);
}

TEST_CASE("find_max returns correct maximum") {
    std::vector<int> v = { 5, 2, 8, -3, 7 };
    CHECK(find_max(v) == 8);
}

TEST_CASE("find_average computes correct average") {
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    CHECK(doctest::Approx(find_average(v)).epsilon(0.001) == 3.0);
}
