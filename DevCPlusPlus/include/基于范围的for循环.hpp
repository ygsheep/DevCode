#include <iostream>
#include <vector>




namespace for_range {





	void test(){

		int arr[] = { 0 ,1 ,2};

		for(const int _ : arr) {
			std::cout << _ << " ";
		}
		std::cout << std::endl;

		std::vector v1{0,1,2,3};

		for(auto _ : arr) {
			std::cout << _ << " ";
		}
		std::cout << std::endl;

		

	}
}
