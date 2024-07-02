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
// template ��ؼ��� ģ���� < ʵ���б� >;	(1)
// extern template ��ؼ��� ģ���� < ʵ���б� >;	(2)	(C++11 ��)
// ��ؼ��� - class��struct �� union
//template class Y<int>; // ������ģ��������ռ��������ʽʵ����

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

// ��ʽʵ���� Z<char> �� Z<char>::f() �ڴ˳��֡�
// ʼ�ղ���Ҫ�Ҳ�ʵ���� Z<char>::g()�����ض�����ж���

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
    const A& ra = a, & rb = a; // ���󶨵�ͬһ��ģ���βζ���
    assert(&ra == &rb);       // ͨ��
  }
  template<typename T>
  concept C1 = true;
  template<typename... Ts>
  concept C2 = true; // ��θ���
  template<typename T, typename U>
  concept C3 = true;

  template<C1 T>         struct s1; // Լ�����ʽ�� C1<T>
  template<C1... T>      struct s2; // Լ�����ʽ�� (C1<T> && ...)
  template<C2... T>      struct s3; // Լ�����ʽ�� (C2<T> && ...)
  template<C3<int> T>    struct s4; // Լ�����ʽ�� C3<T, int>
  template<C3<int>... T> struct s5; // Լ�����ʽ�� (C3<T, int> && ...)
}


namespace B {
  // Լ�����ʽ concept

  //һ����Զ����ƥ��ɹ���concept
  template<typename T>
  concept c1 = true;

  // һ��Լ��Tֻ�����������͵�concept���������Ͱ��� char, unsigned char, short, ushort, int, unsinged int, long�ȡ�
  template<typename T>
  concept integral = std::is_integral_v<T>;
  
  // �з��� ���� ���������͵�concept
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


