#include <iostream>
#include <mutex>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

std::mutex m;


class Data
{
    friend void swap_lock(Data& data1, Data& data2);
    friend void swap_scoped_lock(Data& data1, Data& data2);
    friend void swap_unique_lock(Data& data1, Data& data2);

public:
    Data(std::vector<int> data) : data(std::move(data)) {}
    Data(const Data& other) { data = other.data; }
    Data(Data&& other) noexcept { data = std::move(other.data); }

    Data& operator=(const Data& other) 
    { 
        if (&other == this)
            return *this;

        data = other.data;
        return *this;
    };

    Data& operator=(Data&& other) noexcept 
    { 
        if (&other == this)
            return *this;

        data = std::move(other.data); 
        return *this;
    };

    void printData()
    {
        for (const auto& value : data)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> getData()
    {
        return data;
    }

private:
    std::mutex m;
    std::vector<int> data;
};


void swap_lock(Data& data1, Data& data2)
{
    std::lock(data1.m, data2.m);
    std::lock_guard<std::mutex> lg1(data1.m, std::adopt_lock);
    std::lock_guard<std::mutex> lg2(data2.m, std::adopt_lock);

    auto temp = std::move(data1);
    data1 = std::move(data2);
    data2= std::move(temp);
}


void swap_scoped_lock(Data& data1, Data& data2)
{
    std::scoped_lock sl(data1.m, data2.m);
    auto temp = std::move(data1);
    data1 = std::move(data2);
    data2 = std::move(temp);
}


void swap_unique_lock(Data& data1, Data& data2)
{
    std::unique_lock<std::mutex> u_lock1(data1.m, std::defer_lock);
    std::unique_lock<std::mutex> u_lock2(data2.m, std::defer_lock);

    auto temp = std::move(data1);
    data1 = std::move(data2);
    data2 = std::move(temp);

    std::lock(u_lock1, u_lock2);
}


void swap_data(Data& data1, Data& data2)
{
    for (int i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(2s);
        std::lock_guard<std::mutex> lg(m);
        std::cout << "Swap from thread ID: " << std::this_thread::get_id() << std::endl;
        swap_scoped_lock(data1, data2);
        data1.printData();
        data2.printData();
        std::cout << std::endl;
    }
}


int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    std::vector<int> v2{ 10, 9, 8, 7, 6 };

    Data data1(v);
    Data data2(v2);

    data1.printData();
    data2.printData();
    std::cout << std::endl;

    swap_lock(data1, data2);

    data1.printData();
    data2.printData();
    std::cout << std::endl;

    swap_unique_lock(data1, data2);

    data1.printData();
    data2.printData();
    std::cout << std::endl;

    swap_scoped_lock(data1, data2);
    data1.printData();
    data2.printData();
    std::cout << std::endl;

    std::thread t1(swap_data, std::ref(data1), std::ref(data2));
    std::thread t2(swap_data, std::ref(data1), std::ref(data2));
    t1.join();
    t2.join();

    return 0;
}
