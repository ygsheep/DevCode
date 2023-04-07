#include <cmath>
#include <iostream>
#include <string>

using namespace std;

struct MyException {
  MyException(string s) : msg(s) {}
  string msg;
};

double divisionMethod(int a, int b) {
  if (b == 0) {
    throw MyException("division by zero!");
  }
  return a / b;
}

// 不抛出异常
double divisionMethod1(int a, int b) throw() {
  if (b == 0) {
    cout << "division by zero!" << endl;
  }
  return a / b;
}

void test01() {
  // C++11 之前写法
  try {
    throw -1;
  } catch (int e) {
    cout << "int exception, value: " << e << endl;
  }

  try {
    double a = divisionMethod(10, 0);

  } catch (MyException e) {
    cout << "catch exception: " << e.msg << endl;
  }
}

// 不抛出异常
double divisionMethod2(int a, int b)noexcept  {
  if (b == 0) {
    cout << "division by zero!";
  }
  return a / b;
}



int main() { 
	
	test01();

	return 0;
}
