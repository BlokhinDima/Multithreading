#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;


void increment_clients_number(int&clients_counter, int max_clients)
{
    for (int i = 0; i < max_clients; ++i)
    {
        std::this_thread::sleep_for(1s);
        clients_counter++;
        std::cout << "Clinet added! Clients number: " << clients_counter << std::endl;
    }
}


void decrement_clients_number(int &clients_counter)
{
    std::this_thread::sleep_for(100ms);
    for (;;)
    {
        std::this_thread::sleep_for(2s);
        clients_counter--;
        if (clients_counter == -1) break;
        std::cout << "Clinet removed! Clients number: " << clients_counter << std::endl;
    }
}


int main()
{
    int clients_number = 0;

    std::cout << "Enter maximum clients number: ";
    int max_clients;
    std::cin >> max_clients;
    
    std::thread t1(increment_clients_number, std::ref(clients_number), max_clients);
    std::thread t2(decrement_clients_number, std::ref(clients_number));
    t1.join();
    t2.join();
}
