#pragma once
#include <string>
#include <cstddef>
#include <concepts>
#include <functional>


namespace N {
  
  template<class T>
  class Y {
    void mf();
  };
}

using N::Y;
// template 类关键词 模板名 < 实参列表 >;	(1)
// extern template 类关键词 模板名 < 实参列表 >;	(2)	(C++11 起)
// 类关键词 - class，struct 或 union
//template class Y<int>; // 错误：在模板的命名空间外进行显式实例化

template class N::Y<double>;
template void N::Y<char*>::mf();

template<typename T>
struct Z
{
  void f() {};
  void g();
};

template struct Z<int>;
//Z<int> z1;
//Z<char>* z2;

// 隐式实例化 Z<char> 且 Z<char>::f() 在此出现。
// 始终不需要且不实例化 Z<char>::g()：不必对其进行定义

namespace A {
  template<auto ...>
  struct A {
    friend bool operator==(const A&, const A&) = default;
  };

  //A<'a', 1, 2.5, true,nullptr> a;
  template<A a>
  void f()
  {
    &a;                       // OK
    const A& ra = a, & rb = a; // 都绑定到同一个模板形参对象
    assert(&ra == &rb);       // 通过
  }
  template<typename T>
  concept C1 = true;
  template<typename... Ts>
  concept C2 = true; // 变参概念
  template<typename T, typename U>
  concept C3 = true;

  template<C1 T>         struct s1; // 约束表达式是 C1<T>
  template<C1... T>      struct s2; // 约束表达式是 (C1<T> && ...)
  template<C2... T>      struct s3; // 约束表达式是 (C2<T> && ...)
  template<C3<int> T>    struct s4; // 约束表达式是 C3<T, int>
  template<C3<int>... T> struct s5; // 约束表达式是 (C3<T, int> && ...)
}


namespace B {
  // 约束表达式 concept

  //一个永远都能匹配成功的concept
  template<typename T>
  concept c1 = true;

  // 一个约束T只能是整数类型的concept，整数类型包括 char, unsigned char, short, ushort, int, unsinged int, long等。
  template<typename T>
  concept integral = std::is_integral_v<T>;
  
  // 有符号 并且 是整数类型的concept
  template<typename T>
  concept signed_integral = integral<T> && std::is_signed_v<T>;


  template<c1 T>
  T mul(T a, T b) {
    return a * b;
  }

  template<integral T>
  T add(T a, T b) {
    return a + b;
  }

  template<signed_integral T>
  T subtract(T a, T b) {
    return a - b;
  }

}


