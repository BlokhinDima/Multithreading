#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <execution>
#include <atomic>
#include <windows.h>
#include <string>
#include <iomanip>
#include <random>

const int PBAR_LENGTH = 40;
const char PBAR_SYMBOL_CODE = 219;

const int FIRST_COL_LENGTH = 5;
const int SECOND_COL_LENGTH = 13;
const int THIRD_COL_LENGHT = PBAR_LENGTH + 2;
const int FOURTH_COL_LENGHT = 4;

const int FIRST_COL_START = 0;
const int SECOND_COL_START = FIRST_COL_LENGTH;
const int THIRD_COL_START = SECOND_COL_START + SECOND_COL_LENGTH;
const int FOURTH_COL_START = THIRD_COL_START + THIRD_COL_LENGHT;

using namespace std::chrono_literals;

std::atomic<int> thread_number_counter = 0;

std::mutex m;

HANDLE output_handle = GetStdHandle(STD_OUTPUT_HANDLE);


int getRandomNumber(int lower, int higher)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(lower, higher);
    return dist(rng);
}


void printHeader()
{
    std::cout 
        << std::setw(FIRST_COL_LENGTH) << std::left << "#"
        << std::setw(SECOND_COL_LENGTH) << std::left << "Tread ID"
        << std::setw(THIRD_COL_LENGHT) << std:: left << "Progress Bar"
        << std::setw(FOURTH_COL_LENGHT) << std::left << "Time" << std::endl;
}


void printProgressBar(double current_progress, double max_progress, int thread_number)
{
    COORD pbar_start_coord = {THIRD_COL_START, thread_number};
    SetConsoleCursorPosition(output_handle, pbar_start_coord);

    double progress = current_progress / max_progress * PBAR_LENGTH;
    while (progress >= 0)
    {
        std::cout << PBAR_SYMBOL_CODE;
        progress -= 1;
    }
}


void setCursorOutOfTable()
{
    COORD coord = { FIRST_COL_START, thread_number_counter + 1 };
    SetConsoleCursorPosition(output_handle, coord);
}


void printThreadNumber(int thread_number)
{
    COORD thread_number_print_coord = {FIRST_COL_START, thread_number};
    
    SetConsoleCursorPosition(output_handle, thread_number_print_coord);
    std::cout << thread_number;
}


void printThreadID(int thread_number, std::thread::thread::id thread_id)
{
    COORD thread_id_print_coord = {SECOND_COL_START, thread_number};
    SetConsoleCursorPosition(output_handle, thread_id_print_coord);
    std::cout << thread_id;
}


void printCalculationTime(int thread_number, double time)
{
    COORD calculation_time_print_coord = {FOURTH_COL_START, thread_number};
    SetConsoleCursorPosition(output_handle, calculation_time_print_coord);
    std::cout << time << "s";
}


bool isErrorOccured()
{
    return 1 == getRandomNumber(1, 100);
}


int getRandomDelay()
{
    return  getRandomNumber(1, 10000) % 400;
}


void makeCalculations(int calculation_size)
{
    try
    {
        thread_number_counter++;
        int thread_number = thread_number_counter;

        std::unique_lock<std::mutex> lock(m);
        printThreadNumber(thread_number);
        printThreadID(thread_number, std::this_thread::get_id());

        int calculations_left = calculation_size;
        auto t_start = std::chrono::steady_clock::now();

        for (;;)
        {
            if (calculations_left <= 0)
            {
                auto t_end = std::chrono::steady_clock::now();
                auto t_diff = std::chrono::duration<double>(t_end - t_start);
                printCalculationTime(thread_number, t_diff.count());
                setCursorOutOfTable();
                break;
            }
            else
            {
                lock.unlock();
                int calculation_delay = getRandomDelay();
                std::this_thread::sleep_for(std::chrono::milliseconds(calculation_delay));
                calculations_left--;

                lock.lock();
                if (isErrorOccured())
                {
                    COORD exception_print_coord = {THIRD_COL_START, thread_number};
                    SetConsoleCursorPosition(output_handle, exception_print_coord);
                    throw std::exception::exception("Error! Calculation stopped!");
                }
                else
                {
                    int current_progress = calculation_size - calculations_left;
                    printProgressBar(current_progress, calculation_size, thread_number);
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
        setCursorOutOfTable();
    }
}


int main()
{
    int threads_num;
    std::cout << "Enter threads number: ";
    std::cin >> threads_num;

    int calculation_length;
    std::cout << "Enter calculation lenght: ";
    std::cin >> calculation_length;

    system("CLS");
    printHeader();

    std::vector<std::thread> threads_pool;
    for (int i = 0; i < threads_num; ++i)
    {
        int calculations_part = calculation_length / threads_num;
        threads_pool.push_back(std::thread(makeCalculations, calculations_part));
    }
    for (auto& thread : threads_pool)
    {
        thread.join();
    }

    return 0;
}
