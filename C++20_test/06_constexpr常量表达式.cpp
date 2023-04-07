#include <iostream>

using namespace std;
struct Person
{
	const char * name;
	int age;
	public:
		void speak(){
			cout << "Name = " << name << "\t Age = " << age << endl;
	}
};

template<typename T>
constexpr T display(T t){
	return t;
}

int main(int argc, char *argv[])
{
	struct Person p { "Jack" , 19 };
	// 普通函数	
	struct Person p2 = display(p);
	p2.age += 1;

	p.speak();
	p2.speak();

	constexpr int ret = display(250);

	// ret +=1; // error
	
	// 常量表达式函数
	constexpr struct Person p1 { "Tom" , 20 };
	constexpr struct Person p3 = display( p1 ); // 参数是常量 返回的才是常量
	
	
		



	return 0;
}
