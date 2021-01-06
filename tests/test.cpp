// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>
#include <gtest/gtest.h>

#include "SharedPointer.hpp"
TEST(SharedPointer, ContructorDefaultTest) {
  SharedPointer<int> SP1(new int{0});
  SharedPointer<int> SP2(SP1);
  ASSERT_EQ(SP1.operator bool(), true);
  ASSERT_EQ(SP2.operator bool(), true);
  ASSERT_EQ(SP1.get(), SP2.get());
  ASSERT_EQ(SP1.use_count(), 2);
}
TEST(SharedPointer, TestMainOperators) {
  int b = 50;
  SharedPointer<int> SH_TEST(new int{b});
  ASSERT_EQ(SH_TEST.use_count(), 1);
  ASSERT_EQ(*SH_TEST, b);
}
TEST(SharedPointer, RvalueOperatorTest) {
  SharedPointer<int> SP1(new int{10});
  SharedPointer<int> SP2(std::move(SP1));
  ASSERT_EQ(SP2.use_count(), 1);
}
TEST(SharedPointer, ResetTest) {
  SharedPointer<std::string> s1(new std::string{"hello"});
  std::string *s2 = new std::string("world");
  s1.reset(s2);
  ASSERT_EQ(*s1, "world");
}
TEST(SharedPointer, SwapTest) {
  SharedPointer<int> SP1(new int{10});
  SharedPointer<int> SP2(new int{20});
  SP2.swap(SP1);
  ASSERT_EQ(*SP2, 10);
  ASSERT_EQ(*SP1, 20);
  SharedPointer<char> ch1(new char{'a'});
  SharedPointer<char> ch2(new char{'b'});
  ASSERT_EQ(ch1.use_count(), 1);
  ASSERT_EQ(ch2.use_count(), 1);
  ASSERT_EQ(*ch1, 'a');
  ASSERT_EQ(*ch2, 'b');
  ch1.swap(ch2);
  ASSERT_EQ(ch1.use_count(), 1);
  ASSERT_EQ(ch2.use_count(), 1);
  ASSERT_EQ(*ch1, 'b');
  ASSERT_EQ(*ch2, 'a');
}
TEST(SharedPointer, CheckIsMoveConstructible) {
  ASSERT_EQ(std::is_move_constructible<int &>::value, true);
  EXPECT_TRUE(std::is_move_constructible<SharedPointer<int>>());
  EXPECT_TRUE(std::is_move_constructible<SharedPointer<char>>());
  EXPECT_TRUE(std::is_move_constructible<SharedPointer<size_t>>());
  EXPECT_TRUE(std::is_move_constructible<SharedPointer<std::string>>());
  EXPECT_TRUE(std::is_move_constructible<SharedPointer<uint16_t>>());
}
TEST(SharedPointer, CheckIsMoveAssignable) {
  EXPECT_TRUE(std::is_move_assignable<SharedPointer<int>>());
  EXPECT_TRUE(std::is_move_assignable<SharedPointer<char>>());
  EXPECT_TRUE(std::is_move_assignable<SharedPointer<std::string>>());
  EXPECT_TRUE(std::is_move_assignable<SharedPointer<size_t>>());
  EXPECT_TRUE(std::is_move_assignable<SharedPointer<uint16_t>>());
}
