#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <array>
#include <utility>


template <class Iterator>
void printContainer(Iterator begin, Iterator end)
{
    for (auto itr = begin; itr != end; ++itr)
    {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
}


template <class Iterator>
void searchMinValuePtr(Iterator begin, Iterator end, std::promise<Iterator> prom)
{
    auto min_value_ptr = begin;
    for (auto itr = begin + 1; itr < end; ++itr)
    {
        min_value_ptr = (*itr) < (*min_value_ptr) ? itr : min_value_ptr;
    }
    prom.set_value(min_value_ptr);
}


template <class Iterator>
void selectionSort(Iterator begin, Iterator end)
{
    int shift = 0;
    for (auto itr = begin; itr != end; ++itr)
    {
        std::promise<Iterator> prom;
        std::future<Iterator> future_value = prom.get_future();
        auto async_task = std::async(searchMinValuePtr<Iterator>, begin + shift, end, std::move(prom));

        auto min_value_ptr = future_value.get();
        auto min_value = *min_value_ptr;
        auto temp = *(begin + shift);
        *(begin + shift) = min_value;
        *min_value_ptr = temp;
        shift++;
    }
}


int main()
{
    std::vector<int> v_int = { 1, 4, 6, 7, 8, 10, 56, 43, 101, 567, 2, 5, 7 };
    printContainer(v_int.begin(), v_int.end());
    selectionSort(v_int.begin(), v_int.end());
    printContainer(v_int.begin(), v_int.end());
    std::cout << std::endl;

    std::array<double, 10> v_double = { 10.1, 4.34, 6.445, 7.896, 8.22, 10.04, 56.22, 4.353, 10.167, 5.67 };
    printContainer(v_double.begin(), v_double.end());
    selectionSort(v_double.begin(), v_double.end());
    printContainer(v_double.begin(), v_double.end());
    std::cout << std::endl;
}
