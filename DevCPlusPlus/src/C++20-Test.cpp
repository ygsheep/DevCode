// C++20-Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <format>
#include <cassert>
#include "../include/Log.h";
#include <functional>
#include <vector>
#include <utility>





// 静态断言  static_assert
#define LAZY_STATIC_ASSERT(B) static_assert(B,#B)


int main() {
  constexpr int a = 1;
  LAZY_STATIC_ASSERT(a < 4);


}






namespace A {
  inline namespace v1 {
    void f() {
      std::cout << "A.v1\n";
    };
  }
  namespace v2 {
    void f() {
      std::cout << "A.v2\n";
    };
  }
}

auto main06() -> void {
  A::f(); // A::v1::f() 用做接口的版本升级

}



// noexcept 说明符与运算符
void fo1() noexcept {}
void fo2() noexcept(false){}

auto main05() -> int {
  
  std::cout << std::boolalpha << noexcept(fo1()) << endl;
  std::cout << std::boolalpha << noexcept(fo2()) << endl;

  return 0;
}


#define TEST "test01";
#define TEST "test02" // C4005


void operator""_p(const char* _, size_t size) {
  std::cout << _ << endl;
}

auto f1 = []() {
  std::cout << "1 4 9" << endl;
  return 0;
};
// int n = f1();

template<typename T, typename F>
T& operator | (T& v, F& f) {
  for (auto& i : v)
  {
    f(i);
  }
  return v;
}

auto test1 = []() {
  std::vector v {1, 2, 3};
  std::function f = [](const int& i) { std::cout << i << " ";  };
  auto f2 = [](int& i) { i *= i; };
  v | f2 | f;
};

void rf1(int&&){}
// 值类别
int main04() {
  /*
    T&  左值
    T&& 右值 
    const T& 能够接收右值
  */
  int a = 1;
  int& ra = a; // ra 是 a 的引用： 左值
  const int& rra = 1;
  int&& rra1 = 1;
  using T1 = decltype((ra)); // int&
  using T2 = decltype((1)); // int 纯右值
  using T3 = decltype((std::move(1))); //int&& 亡值
  using T4 = decltype(((int&&)ra)); // int&&

  // int& p = 1; // error: 1 是纯右值

  // 纯右值 (prvalue)、亡值 (xvalue)、左值 (lvalue)
  /* 纯右值： 
   （除了字符串字面量之外的）字面量，例如 42、true 或 nullptr；
	*/
  //using T2 = decltype((L"a"));
  const wchar_t* l1 = L"a";

  rf1(1);
  //rf1(a); //无法将右值引用绑定到左值
  //rf1(rra1); 无法将右值引用绑定到左值
  rf1(std::move(a));
  
  return 0;
}



struct Test
{
  int v{};
  int operator -(const Test& b) const {
    return this->v - b.v;
  }
  auto operator <=>(const Test& b) const = default;

};

// 三路运算
int main03(void) {
  double a = 1.0, b = 2.0;

  auto ret = a <=> b;

  if (ret > 0) {
    ::std::cout << "a > b" << endl;
  }
  else if (ret < 0) {
		::std::cout << "a < b" << endl;
  }
  else {
		::std::cout << "a == b" << endl;

  }
  return 0;
}

