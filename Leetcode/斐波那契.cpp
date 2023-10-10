#include <fmt/core.h>
#include <iostream>
#include <string>

size_t test(int k){
	size_t arr[k];
	arr[0] = 1;
	arr[1] = 1;
	for (int i = 2; i < k; i++) {
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	return arr[k - 1];
}


int main(int argc, char *argv[])
{
	if (argc < 2) {
		fmt::print("没有输入值！");
		return 1; // quit
	}
	int a = std::stoi(argv[1]);
	fmt::print("第{}个月有{}只🐇",a,test(a));

}

