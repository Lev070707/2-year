#include <gtest/gtest.h>
#include "employee.h"
#include "fileops.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>

static void rm_if_exists(const char* name) { std::remove(name); }

TEST(FileOps_Single, WriteReadSingleEmployee) {
    const char* fname = "ut_one.bin";
    rm_if_exists(fname);

    employee e{};
    e.num = 7;
    std::strncpy(e.name, "Eve", sizeof(e.name) - 1);
    e.hours = 12.5;

    std::vector<employee> w = { e };
    std::string err;
    ASSERT_TRUE(writeEmployees(fname, w, err)) << err;

    std::vector<employee> r;
    ASSERT_TRUE(readEmployees(fname, r, err)) << err;
    ASSERT_EQ(r.size(), 1u);
    EXPECT_EQ(r[0].num, 7);
    EXPECT_STREQ(r[0].name, "Eve");
    EXPECT_DOUBLE_EQ(r[0].hours, 12.5);

    rm_if_exists(fname);
}

TEST(FileOps_Multiple, WriteReadMultipleEmployees) {
    const char* fname = "ut_many.bin";
    rm_if_exists(fname);

    employee a{}; a.num = 1; std::strncpy(a.name, "Alice", sizeof(a.name) - 1); a.hours = 40.0;
    employee b{}; b.num = 2; std::strncpy(b.name, "Bob", sizeof(b.name) - 1); b.hours = 35.5;
    employee c{}; c.num = 3; std::strncpy(c.name, "Carl", sizeof(c.name) - 1); c.hours = 20.25;

    std::vector<employee> w = { a, b, c };
    std::string err;
    ASSERT_TRUE(writeEmployees(fname, w, err)) << err;

    std::vector<employee> r;
    ASSERT_TRUE(readEmployees(fname, r, err)) << err;
    ASSERT_EQ(r.size(), 3u);
    EXPECT_EQ(r[0].num, 1);
    EXPECT_STREQ(r[1].name, "Bob");
    EXPECT_DOUBLE_EQ(r[2].hours, 20.25);

    rm_if_exists(fname);
}

TEST(FileOps_Error, ReadNonexistentFileFails) {
    const char* fname = "this_file_should_not_exist_12345.bin";
    std::string err;
    std::vector<employee> r;
    EXPECT_FALSE(readEmployees(fname, r, err));
    EXPECT_FALSE(err.empty());
}

TEST(Salary_Basic, MultiplyHoursByRate) {
    employee e{}; e.num = 10; std::strncpy(e.name, "Test", sizeof(e.name) - 1); e.hours = 8.0;
    double rate = 15.0;
    double salary = e.hours * rate;
    EXPECT_DOUBLE_EQ(salary, 120.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
