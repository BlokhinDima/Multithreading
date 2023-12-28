#include <iostream>
#include <future>
#include <vector>
#include <array>
#include <thread>
#include <algorithm>


template <class Iterator, typename F>
F forEach(Iterator begin, Iterator end, F func)
{
	size_t curr_size = std::distance(begin, end);
	if (curr_size == 1)
	{
		return std::for_each(begin, end, func);
	}
	auto mid = begin;
	std::advance(mid, curr_size / 2);
	auto ft_res = std::async(forEach<Iterator, F>, begin, mid, func);
	auto l_res = forEach(mid, end, func);
}


template <typename T>
void multiplyByThree(T& x)
{
	x *= 3;
}


template <typename T>
void square(T& x)
{
	x *= x;
}


template <class Iterator>
void printContainer(Iterator begin, Iterator end)
{
	for (auto itr = begin; itr != end; ++itr)
	{
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
}


int main()
{
	std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	printContainer(v.begin(), v.end());
	forEach(v.begin(), v.end(), multiplyByThree<int>);
	printContainer(v.begin(), v.end());
	std::cout << std::endl;

	std::array<double, 10> v2{ 1.01, 2.22, 3.056, 4.02, 5.567, 6.23, 7.333, 8.333, 9.13, 10.0 };
	printContainer(v2.begin(), v2.end());
	forEach(v2.begin(), v2.end(), square<double>);
	printContainer(v2.begin(), v2.end());
	std::cout << std::endl;
}
