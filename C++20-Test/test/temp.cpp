#include <iostream>

template<char ...C>
struct FixStringOld
{
    constexpr static std::size_t N = sizeof...(C) + 1;
    constexpr static const char data[N] = { C...,0 };
};

	#define F(...) f(0,##__VA_ARGS__)

	void f(...){};

int main()
{
  FixStringOld< 'h', 'e', 'l','l','o','w', 'o', 'r','l','d'> f1;
  FixStringOld< 'a', 'b', 'c' > f2;
  FixStringOld< 'a', 'b', 'd' > f3;
  
  F(0,1);

  
}
