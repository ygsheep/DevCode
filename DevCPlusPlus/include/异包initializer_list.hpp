#pragma once
#include <initializer_list>
#include <iostream>

namespace mylist {

class P {
public:
  P(int a, int b) {
    std::cout << "P(int,int): "
              << "a= " << a << ",b= " << b << std::endl;
  };
  P(std::initializer_list<int> vals) {
    std::cout << "P(std::initializer_list<int>) valuse: ";
    for (auto v : vals) {
      std::cout << v << " ";
    }
    std::cout << "\n";
  }
};

inline void test() {

  P p0(1, 2);
  P p1({1, 2});
  P p2{1, 2, 3};
  P p3 = {1, 2, 3, 4};
}
} // namespace mylist
