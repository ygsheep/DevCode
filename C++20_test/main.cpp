#include <algorithm>
#include <iostream>
#include <string>

using namespace std;


void operator""_p(const char * str,size_t len){
	std::cout << str << "\tsizes: " << len << std::endl;
}

int max(int a,int b){
	return a > b ? a : b;
}

int main(int argc, char *argv[]){
	"sss"_p;
	"printf('\n');"_p;
	string path = "Word";
	return 0;
}
