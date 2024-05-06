#include <iostream>
#include <queue>
#include <thread>
#include <random>
#include <condition_variable>
#include <atomic>

std::queue<int> temperatureQueue;
std::mutex queueMutex;
std::condition_variable queueCV;
std::atomic<bool> isThread1Running(true);

bool shouldWakeUp()
{
    return !temperatureQueue.empty() || !isThread1Running;
}

void pushTemperature(int temperature)
{ 
    std::unique_lock<std::mutex> lock(queueMutex); // Acquire the lock on the queueMutex using std::unique_lock.
    queueCV.wait(lock, []{ return temperatureQueue.size() < 10; }); // Wait until the condition variable queueCV is signaled and the size of the temperatureQueue is less than 10.
    temperatureQueue.push(temperature);
    std::cout << "Thread 1 pushed the temperature value onto the queue" << std::endl;
    queueCV.notify_all(); // Notify all threads waiting on the condition variable queueCV.
}

void thread1()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 50);
    int i = 0;
    while ( i < 100 ) { 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  
        int ran_temp = dist(gen); // Generate a random temperature using the random number generator dist
        pushTemperature(ran_temp);
        i++;
    }
    isThread1Running = false; // Set the value of isThread1Running to false.
    queueCV.notify_all(); // Notify all threads waiting on the condition variable queueCV.
}

void convertTemperature(int temperature)
{
    // Convert temperature to Celsius
    double celsius = (temperature - 32) * 5 / 9.0;
    std::cout << "Thread 2 converted temperature: " << temperature << "F to " << celsius << "C" << std::endl;
}

void convertAndReportTemperature()
{
    while (isThread1Running == true || temperatureQueue.empty() == false) { // Enter a loop while the isThread1Running flag is true or the temperatureQueue is not empty
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCV.wait(lock, []{ return shouldWakeUp; }); // Wait until the condition variable queueCV is signaled and either the temperatureQueue is not empty or isThread1Running is true
        if (!temperatureQueue.empty() ) {
            int ret_temp = temperatureQueue.front();
            temperatureQueue.pop();
            lock.unlock(); // Release the lock on the queueMutex
            convertTemperature(ret_temp); // Call the convertTemperature function with the retrieved temperature value.
        }
    }
    while (isThread1Running == true || temperatureQueue.empty() == false) { //Repeat the loop.
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCV.wait(lock, []{ return shouldWakeUp; });
        if (!temperatureQueue.empty()) {
            int ret_temp = temperatureQueue.front();
            temperatureQueue.pop();
            lock.unlock();
            convertTemperature(ret_temp);
        }
    }
}

int main()
{
    std::thread t1(thread1);
    std::thread t2(convertAndReportTemperature);

    t1.join();
    t2.join();

    std::cout << "Threads completed." << std::endl;

    return 0;
}
