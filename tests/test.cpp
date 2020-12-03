// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>
#include <gtest/gtest.h>
#include "SharedPointer.hpp"
SharedPointer<int> sp1;
TEST(CheckContructor, Test1) {
   EXPECT_EQ(sp1.use_count(), 0);
   EXPECT_EQ((sp1.operator bool()), 0);
   EXPECT_EQ(sp1.use_count(), 0);
}