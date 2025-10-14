#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <functional>
#include <doctest.h>
#include <vector>
#include <thread>
#include <future>
#include "average.h"
#include "min_max.h"

TEST_CASE("Average thread sets promise") {
    std::vector<int> v = { 2,4,6 };
    std::promise<double> p;
    std::future<double> f = p.get_future();
    std::thread t(averageThread, std::cref(v), &p);
    t.join();
    double res = f.get();
    CHECK(res == doctest::Approx(4.0));
}

TEST_CASE("MinMax thread sets promise") {
    std::vector<int> v = { 7,2,8,2,10 };
    std::promise<std::pair<int, int>> p;
    std::future<std::pair<int, int>> f = p.get_future();
    std::thread t(minMaxThread, std::cref(v), &p);
    t.join();
    auto res = f.get();
    CHECK(res.first == 2);
    CHECK(res.second == 10);
}

TEST_CASE("Both threads fulfill promises") {
    std::vector<int> v = { 1,3,5,7,9 };
    std::promise<double> pavg;
    std::future<double> favg = pavg.get_future();
    std::promise<std::pair<int, int>> pmm;
    std::future<std::pair<int, int>> fmm = pmm.get_future();

    std::thread ta(averageThread, std::cref(v), &pavg);
    std::thread tm(minMaxThread, std::cref(v), &pmm);
    ta.join();
    tm.join();

    double avg = favg.get();
    auto mm = fmm.get();

    CHECK(avg == doctest::Approx(5.0));
    CHECK(mm.first == 1);
    CHECK(mm.second == 9);
}