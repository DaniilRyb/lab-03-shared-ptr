// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>
#include <gtest/gtest.h>
#include "SharedPointer.hpp"
TEST(SharedPointer, ContructorDefaulTest) {
  SharedPointer<int> SP1(new int{0});
  SharedPointer<int> SP2(SP1);
  ASSERT_EQ(SP1.operator bool(), true);
  ASSERT_EQ(SP2.operator bool(), true);
  ASSERT_EQ(SP1.get(), SP2.get());
  ASSERT_EQ(SP1.use_count(), 2);
}
TEST(SharedPointer, Operator) {
  int b = 50;
  SharedPointer<int> SH_TEST(&b);
  ASSERT_EQ(SH_TEST.use_count(), 1);
  ASSERT_EQ(*SH_TEST, b);
}
TEST(SharedPointer, RvalueOperatorTest) {
  int a = 10;
  SharedPointer<int> SP1(&a);
  SharedPointer<int> SP2(std::move(SP1));
  ASSERT_EQ(SP1.get(), SP1.get());
  ASSERT_EQ(SP2.use_count(), 1);
}
TEST(SharedPointer, SwapTest) {
  int a = 10;
  int b = 20;
  SharedPointer<int> SP1(&a);
  SharedPointer<int> SP2(&b);
  SP2.swap(SP1);
  ASSERT_EQ(*SP2, 10);
  ASSERT_EQ(*SP1, 20);
}
TEST(SharedPointer, IsMoveConstructible) {
  SharedPointer<int> test_sp1(new int{10});
  ASSERT_EQ(std::is_move_constructible<int&>::value, true);
}

TEST(SharedPointer, IsMoveAssignable) {
  SharedPointer<int> test_sp2(new int{10});
  ASSERT_EQ(std::is_move_assignable<int&>::value, true);
}
