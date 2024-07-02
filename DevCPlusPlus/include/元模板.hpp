#ifndef 元模板_H

#define 元模板_H
#include <utility>
#include <cstddef>
#include <cstdio>
#include <ios>
#include <iostream>
#include <type_traits>
#include <utility>
#include <cassert>



namespace MyTemplate{
	using namespace std;

	#define F(...) f(0,##__VA_ARGS__)
	
	template<typename T>
	void f(T...){};
	
	template<char ..._C>
		struct FixStringOld {
			constexpr static size_t N = sizeof...(_C) + 1;
			constexpr static const char data[N] = { _C...,0 };


			void InfoPrint() const {
				cout << "Type: FixStringOld" << "\tleght: " << N \
					<< "\nString: " << data << endl;
			}
		};

	// 只用声明，尾置返回
	template<char ..._C>
		auto MakeFixStringOld(FixStringOld<_C...>) -> FixStringOld<_C...>;
	
	template<size_t M, size_t N>
		constexpr char GetFixStringOld(const char (&arr)[N]) {
			return arr[ M < N ? M : N - 1];
		}

	// 生成char数据
	#define MAKECHARINDEX(n,str)       GetFixStringOld<0x##n##0>(str), GetFixStringOld<0x##n##1>(str),\
																	   GetFixStringOld<0x##n##2>(str), GetFixStringOld<0x##n##3>(str),\
																	   GetFixStringOld<0x##n##4>(str), GetFixStringOld<0x##n##5>(str),\
																	   GetFixStringOld<0x##n##6>(str), GetFixStringOld<0x##n##7>(str),\
																	   GetFixStringOld<0x##n##8>(str), GetFixStringOld<0x##n##9>(str),\
																	   GetFixStringOld<0x##n##a>(str), GetFixStringOld<0x##n##b>(str),\
																	   GetFixStringOld<0x##n##c>(str), GetFixStringOld<0x##n##d>(str),\
																	   GetFixStringOld<0x##n##e>(str), GetFixStringOld<0x##n##f>(str)

	#define MAKECHARINDEX64_L(str)     MAKECHARINDEX(0,str),MAKECHARINDEX(1,str),\
                                     MAKECHARINDEX(2,str),MAKECHARINDEX(3,str)

	#define MAKECHARINDEX64_H(str)     MAKECHARINDEX(4,str),MAKECHARINDEX(5,str),\
                                     MAKECHARINDEX(6,str),MAKECHARINDEX(7,str)
	#define MAKECHARINDEXSEQUENCE(str) MAKECHARINDEX64_L(str),MAKECHARINDEX64_H(str)
	
	#define MAKESTRINGCHAR(str) decltype(FixStringOld<MAKECHARINDEXSEQUENCE(str)>{})
	

	inline void test(){
		cout << "元模板 Testing \n";
		F(0,1); // f(0,0,1)
		

		FixStringOld<'a','b','c'> f1;
		FixStringOld<'a','b','d'> f2;
		// 不是同一类型，虽然所站内存相同
		using _tf1 = decltype(f1);
		using _tf2 = decltype(f2);
		
		cout << std::boolalpha<< std::is_same<_tf1, _tf2>::value << endl;


		using _ty3 = decltype(MakeFixStringOld(f1));
		

		cout << GetFixStringOld<1>("hello world") << endl;

		MAKESTRINGCHAR("hello world") s1;

		s1.InfoPrint();




	}
}




#endif /* end of include guard: 元模板_H */
