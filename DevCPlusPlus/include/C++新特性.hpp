#include <algorithm>
#include <iostream>
#include <limits>

namespace newTest {

// 非类型模板形参占位符
template <auto N> void f() { std::cout << N << std::endl; }

// auto 占位符
void autoTest() {

  // auto 关键字的新定义
  // FIX: 类型不一致，gcc无法通过编译
  // auto x = 1, y = 2.1; // NOTE: x: int, y: double
  // 编译错误❌: 对‘auto’不一致的演绎：先是‘int’然后是‘double’

  // NOTE: 虽然结果为1，但是 auto 会选择强类型
  // 所以 decltype(x) = double
  auto x1 = true ? 1 : 2.1;
  std::cout << "x1的类型为" << abi::__cxa_demangle(typeid(x1).name(), 0, 0, 0)
            << "\n";
  static_assert(std::is_same<decltype(x1), double>::value);

  const int cvi = 1; // cv限定
  auto j = cvi;      // 自动忽略cv限定符

  // 引用初始化
  int i = 1;
  int &j1 = i;
  auto m = j1;

  // 万能引用
  auto &&m1 = i;
  auto &&j2 = 6;

  int arr[5];
  auto &&index = arr; // 推导为数组的指针

  // lambda 表达式的形参中使用auto
  auto l = [](auto a, auto b) { return a + b; };
  auto retval = l(1, 2.0);

  f<'a'>();
}

struct A {
  A(const std::string &n, const int &a) : name_(n), age_(a) {}

public:
  std::string name_;
  int age_;
};

template <decltype(auto) N> void func01() {
  std::cout << "N的类型为：" << abi::__cxa_demangle(typeid(N).name(), 0, 0, 0)
            << "  N = " << N << std::endl;
}

template <typename T, typename U> auto add(T t, U u) -> decltype(t + u) {
  return t + u;
}

void decltypeTest() {
  // NOTE: gcc 扩展提供 typeof
  int a = 0;
  typeof(a) b = 5; // 推导为 int b = 5;

  // NOTE: C++标准提供 typeid
  int x1 = 0;
  double x2 = 1.1;
  // GCC需要使用解码，可以显示更适合人类阅读 abi::__cxa_demangle()
  std::cout << abi::__cxa_demangle(typeid(x1).name(), 0, 0, 0) << std::endl;
  std::cout << abi::__cxa_demangle(typeid(x1 + x2).name(), 0, 0, 0)
            << std::endl;
  std::cout << abi::__cxa_demangle(typeid(double).name(), 0, 0, 0) << std::endl;
  // MSVC
  // std::cout << typeid(x1).name() << std::endl;
  // std::cout << typeid(x1 + x2).name() << std::endl;
  // std::cout << typeid(double).name() << std::endl;

  // NOTE: decltype 用法和 typeof 类似
  x1 = 1;
  decltype(x1) x3 = 2;

  // TODO: 推导规则
  // decltype(e) (其中e的类型为T) 的推导规则有五条：
  // 1、如果 e
  // 是一个未加括号的标识符表达式（结构化绑定除外）或者未加括号的类成员访问
  //	则decltype(e)
  // 推断出的类型是e的类型T。如果不存在这样的类型，或者e是一组重载函数，则无法推导。
  // 2、如果e是一个函数调用或者仿函数调用，那么decltype(e)
  // 推断出类型为返回值类型。 3、e 的类型为 T 的左值，则decltyoe(e)是 T& 4、e
  // 的类型为 T 的将亡值，则decltyoe(e)是 T&& 5、除以上情况，则 decltyoe(e)是 T

  const int &&func();
  const A *As1 = new A("tom", 10);
  int &a_left = a;
  // 推导类型为函数返回值 const int &&
  decltype(func()) a0 = 1;
  decltype((As1->age_)) cvi = 1;

  // a) 如果 表达式 的值类别是亡值，将会 decltype 产生 T&&；
  decltype(static_cast<int &&>(a)) a1 = 1;

  // b) 如果 表达式 的值类别是左值，将会 decltype 产生 T&；
  decltype(static_cast<int &>(a)) a2 = a;
  decltype(a_left) a_left1 = a;

  // c) 如果 表达式 的值类别是纯右值，将会 decltype 产生 T。
  decltype(1) a_right_0 = 1;
  decltype(As1->age_) a_right_1 =
      1; // 未加括号的成员变量时，父对象的cv限定符会被忽略。

  // 用decltype的推导规则来推导auto
  auto ax1 = (a);           // int
  decltype(auto) ax2 = (a); // int&

  // 为非类型模板形参占位符
  ::newTest::func01<'a'>();

  int i = 33;
  decltype(i) j = i * 2;

  std::cout << "i = " << i << ", "
            << "j = " << j << '\n';

  std::cout << "i 和 j 的类型相同吗？"
            << (std::is_same_v<decltype(i), decltype(j)> ? "相同" : "不同")
            << '\n';
  auto f = [](int a, int b) -> int { return a * b; };

  decltype(f) g = f; // lambda 的类型是独有且无名的
	std::cout << "g: " << abi::__cxa_demangle(typeid(g).name(),0,0,0) << std::endl;
  i = f(2, 2);
  j = g(3, 3);

  std::cout << "i = " << i << ", "
            << "j = " << j << '\n';
}

void test() {
  // 求最大值与最小值
  std::cout << "std::numeric_limits<long>::max() = "
            << std::numeric_limits<long>::max() << std::endl;
  std::cout << "std::numeric_limits<long long>::max() = "
            << std::numeric_limits<long long>::max() << std::endl;

  autoTest();
  decltypeTest();
};
} // namespace newTest
