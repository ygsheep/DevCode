#pragma once
#include <cstdlib>
#include <fstream>
#include <iostream>


// C++ primer plus
// 4.复合类型


namespace CPP_4 {
	


	void test(){
		char shift_size = 'S';
		std::cout << ( int ) shift_size << std::endl;

		constexpr size_t ArSize = 20;
		char name[ArSize];
		
		// std::cin.get(name,ArSize).get();

		// std::cout << name << std::endl;

		// C++11 初始化
		char first_date[] = { "hello word" };

#include <cctype>
		if(isalpha('\0') and true){
			std::cout << "true" << std::endl;
		}else{
			std::cout << "false" << std::endl;
		}

		int Number[ArSize];

		char ch;


		std::ofstream inFile;

		inFile.open("test.txt");
		if(not inFile.is_open()){
			std::exit(0);
		}

		do {
			std::cin >> ch;
			inFile << ch;
		} while (isdigit(ch));

		inFile.close();


	};
	
}


