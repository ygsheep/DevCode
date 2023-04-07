#include <form.h>
#include <iostream>
#include <vector>

using std::endl;

// 依次有默认值
void func(int, int, int = 3);
void func(int, int = 2, int);
void func(int = 1, int, int);

// 错误 无法编译
// void func(int, int = 2, int);
// void func(int, int, int = 3);
// void func(int = 1, int, int);

//  
void func(int a, int b, int c) { std::cout << a << b << c << endl; }

int main() {
  func();
  return 0;
}
