#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

// 数组分成三类
// 主元(pivot) 小于等于<=的部分 大于等于>=的部分
// @retur when left < right
// TODO:define function
template <typename T>
void quickSort(::std::vector<T> &nums, int left, int right);

template <typename T>
inline void PrintVector(::std::vector<T> nums)
{
	::std::cout << "[";
	for (auto num : nums) {
		::std::cout << num << ",";
	}
	::std::cout << "]\n";
}

int main()
{
	::std::vector<int> v1 { 3, 7, 1, 2, 5, 4, 8, 6, 9 };
	quickSort(v1,0,v1.size() - 1);
	PrintVector(v1);
	return 0;
}
template <typename T>
void quickSort(::std::vector<T> &nums, int left, int right)
{
	if (left > right) return;
	PrintVector(nums);
	
}
