#include <iostream>

using std::cout;

struct X {
  void f() { std::cout << "f1" << std::endl; };
// f 重载
  void f(int) { std::cout << "f2" << std::endl; };
};
 
void f2(void (X::*p)(), X* x) { (x->*p)(); } // 指针使用 -> 访问
void f2(void (X::*p)(), X& x) { (x.*p)(); }

void f3(void (X::*p)(int), X& x) { (x.*p)(0); }

int main(int size, char *argv[]) {
  void (X::*p)() = &X::f;
  X x;
  (x.*p)();
	
	f2(&X::f, x);
	f2(&X::f, &x);

	void (X::* pi)(int) = &X::f;

	f3(&X::f, x);


  return 0;
}
