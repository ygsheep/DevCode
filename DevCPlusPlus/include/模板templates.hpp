#include <iostream>



namespace templates {
	

	void printf(){};

	template<class T, typename ...Argv>
		void printf(T first, Argv... args){
			std::cout << first << std::endl;
			printf(args...);
		};


	void test(){

		printf(0,1.0,'b',"bcde");

	};
}
