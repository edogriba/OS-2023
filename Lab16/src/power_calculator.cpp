#include <cse4733/power_calculator.hpp>
#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

namespace cse4733 {

PowerCalculator::PowerCalculator(): is_running(true) {}

void PowerCalculator::start() {
    std::thread t1(&PowerCalculator::thread1_task, this);
    std::thread t2(&PowerCalculator::thread2_task, this);

    t1.join();
    t2.join();
}

void PowerCalculator::thread1_task() {
    std::random_device rd;  // Create an instance of std::random_device
    std::mt19937 gen(rd()); // Create an instance of std::mt19937
    std::uniform_int_distribution<> distrib_base(1,100); //Create a uniform integer distribution for the integer values (1 - 100)
    std::uniform_int_distribution<> distrib_power(1,10); // Create a uniform integer distribution for the power value (1-10)
    std::chrono::microseconds time_limit(250);
    auto start_time = std::chrono::high_resolution_clock::now();    
    std::chrono::duration<double> elapsed_time;
    while (true) {
        const std::lock_guard<std::mutex> lock(mtx); // Create an instance of std::lock_guard 
        int rand_value_base = distrib_base(gen);
        int rand_value_power = distrib_power(gen);
        data_queue.push(std::make_pair(rand_value_base, rand_value_power)); // Add random value and random power to the queue
        auto end_time = std::chrono::high_resolution_clock::now();
        elapsed_time = end_time - start_time;
        if ( elapsed_time > time_limit) {
            break;
        }
    }
    is_running = false;
     
}   

void PowerCalculator::thread2_task() {
    while (is_running) {
        int base = 0;
        int power = 0 ;   
        const std::lock_guard<std::mutex> lock(mtx); // Create an instance of std::lock_guard
        if (!data_queue.empty()) {
            std::pair<int, int> element =  data_queue.front();
            base = element.first;
            power = element.second;
            data_queue.pop();
            if ( base != 0  && power != 0 ) {
                unsigned long long result = pow(base, power); // Calculate the power value
                std::cout << "Power of " << base << " raised to the " << power << " is " << result << std::endl;
            }
        }
    }
}
}

