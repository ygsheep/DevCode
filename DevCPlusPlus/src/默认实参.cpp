#include <iostream>
#include <memory>

using namespace std;

class Base
{
public:
	virtual void f(int a = 8) { cout << "Base:" << a << endl; };
};

class Derived: public Base
{
public:
	void f(int a) override { cout << "Derived:" << a << endl; };

};

struct A
{
	virtual void f();
};

struct B: A
{
	void f() final;
};
struct C final: B
{
	//void f() override;// ����f ���ܱ����ǣ���Ϊ���� B ���� final ��

};


int main(void) {

	unique_ptr<Base> ptr{ new Derived };
	ptr->f();

	Base* pb = new Derived();
	pb->f();

	return 0;
}