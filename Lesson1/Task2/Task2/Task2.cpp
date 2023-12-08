#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <execution>
#include <condition_variable>

std::once_flag print_cores_flag;


void printCoresNum()
{
    std::cout << "Cores: " << std::thread::hardware_concurrency() << std::endl;
}


std::vector<int> createRandomNumbersVector(int size)
{
    std::vector<int> v(size);
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist(0, size);
    std::generate(std::execution::par, v.begin(), v.end(), [&]() { return dist(gen); });
    return v;
}


void sumVectorsParts(std::vector<int>& v1, std::vector<int>& v2, std::vector<int>& sum, 
    int start_idx, int end_idx)
{
    for (int i = start_idx; i < end_idx; ++i)
    {
        sum[i] = v1[i] + v2[i];
    }
}


std::vector<int> sumVectorsInThreads(std::vector<int>& v1, std::vector<int>& v2, int threads_num)
{
    std::call_once(print_cores_flag, printCoresNum);

    std::vector<int> sum(v1.size());

    std::vector<std::thread> threads_pool;
    for (int i = 0; i < threads_num; ++i)
    {
        const int part_size = v1.size() / threads_num;
        const int start_idx = part_size * i;
        int end_idx = part_size * (i + 1);
        if (i == threads_num - 1)
        {
            end_idx = v1.size();
        }
        threads_pool.push_back(
            std::thread(
                sumVectorsParts, std::ref(v1), std::ref(v2), std::ref(sum), start_idx, end_idx)
        );
    }
    for (auto& thread : threads_pool)
    {
        thread.join();
    }

    return sum;
}


void printVector(std::vector<int>& v)
{
    for (const auto& el : v)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}


std::vector<int> sumVectors(const std::vector<int>& v1, const std::vector<int>& v2)
{
    std::vector<int> result(v1.size(), 0);
    for (size_t i = 0; i < v1.size(); ++i)
    {
        result[i] = v1[i] + v2[i];
    }
    return result;
}


bool compareVectors(const std::vector<int>& v1, const std::vector<int>& v2)
{
    if (v1.size() != v2.size())
        return false;

    for (size_t i = 0; i < v1.size(); ++i)
    {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}


int main()
{
    bool sizes_printed = false;

    for (int threads_num = 1; threads_num <= 16; threads_num *= 2)
    {
        std::vector<int> sizes{ 1000, 10000, 100000, 1000000 };
        std::vector<std::chrono::duration<double>> t_diffs;

        for (const auto& size : sizes)
        {
            auto v1 = createRandomNumbersVector(size);
            auto v2 = createRandomNumbersVector(size);

            auto t_start = std::chrono::steady_clock::now();
            auto sum = sumVectorsInThreads(v1, v2, threads_num);
            auto t_end = std::chrono::steady_clock::now();
            auto t_diff = std::chrono::duration<double> (t_end - t_start);
            t_diffs.push_back(t_diff);

            auto answer = sumVectors(v1, v2);
            if (!compareVectors(sum, answer))
                std::cout << "ERROR!!!" << std::endl;
        }

        if (!sizes_printed)
        {
            std::cout << "Vectors sizes: " << "\t";
            for (const auto& size : sizes)
                std::cout << size << "\t\t";
            std::cout << std::endl;
            sizes_printed = true;
        }

        std::cout << "Threads_num: " << threads_num << "\t";
        for (const auto& t_diff : t_diffs)
        {
            std::cout << t_diff.count() << "s" << "\t";
        }
        std::cout << std::endl;

    }
    std::cout << std::endl;
}
