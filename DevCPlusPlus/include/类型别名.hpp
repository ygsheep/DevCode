#ifndef 类型别名_H

#define 类型别名_H
#include <iostream>

namespace typedefTest {

typedef int int_t; // 声明 int_t 为类型 int 的别名
typedef char chart_t, *char_ptr, (*fp)(void); // char_t -> char 
																							// char_ptr -> char*
																							// fp -> char(*)(void)


void test() {}
} // namespace typedefTest

#endif /* end of include guard: 类型别名_H */
