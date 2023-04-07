//Header.h
#include <string>

namespace Test
{
    namespace old_ns
    {
        std::string Func() { return std::string("Test::old_ns"); }
    }
		// 内联命名空间 using namespace ... 默认使用new_ns
    inline namespace new_ns
    {
        std::string Func() { return std::string("Test::new_ns"); }
    }
}

// #include "header.h"
#include <string>
#include <iostream>

using std::cout;

int main() {
  using namespace Test;
  using namespace std;
  cout << Func() << std::endl; // "Hello from new"
  cout << old_ns::Func() << std::endl;
  return 0;
}
