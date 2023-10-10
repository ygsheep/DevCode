#pragma once
#include <fmt/core.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "labmda-demo.hpp"

void test01();
void test02();

int main(int argc, char **arg) {

  // labmda递归
  // test01();

  // 用户自定义字面量
  test02();
  // 成员指针
  func01();

  return 0;
}

void test01() {
  /**
   * C++23才支持
   */
  // constexpr auto t = [](this const auto & self,int a){
  // 	if (a == 0 ) return 1;
  // 	else return self( a - 1 ) * a;
  // };
  // constexpr size_t N = t(5);
  // fmt::print("{}",N);
}
void operator""_p(const char *str, size_t len) {
  fmt::print("{}\nlen: {}", str, len);
}
void test02() {
	"123456"_p;
}


