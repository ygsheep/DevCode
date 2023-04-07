#include <cstddef>
#include <cstring>
#include <iostream>
#include <cassert>
#include <string>


using namespace std;
typedef unsigned long long ull;

char *CreateArray(size_t size) {
	// 运行时断言
  assert(size > 0);
  char *Array = new char[size];
  return Array;
}

int main() {
	
	// 静态断言，编译时判断
	static_assert(sizeof(long) == 8, "❌不是64位系统");
	cout << "64bit Linux long 大小： " << sizeof(long) << endl;
	cout << "64bit Linux char指针 大小：" << sizeof(char*) << endl;
	cout << "64bit Linux unsigned long long 大小：" << sizeof(ull) << endl;

	
	char * buf = CreateArray(16);
	strcpy(buf, "hello, word!");
	cout << "buf = " << buf << endl;
	delete[] buf;


	return 0;
}
