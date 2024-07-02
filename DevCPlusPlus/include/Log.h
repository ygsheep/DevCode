#pragma once
#include <iostream>
#include <string>

using namespace std;
class Log
{
private:
	Log() {};
public:
	inline static void show(string message) {
		cout << message << endl;
	}
};

void func(int&&) {
	
};


