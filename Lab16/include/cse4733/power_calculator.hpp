#ifndef POWER_CALCULATOR_HPP
#define POWER_CALCULATOR_HPP

#include <queue>
#include <mutex>
#include <atomic>
#include <utility>

namespace cse4733 {

class PowerCalculator
{
public:
    PowerCalculator();
    void start();

private:
    std::queue<std::pair<int, int>> data_queue;
    std::mutex mtx;
    std::atomic<bool> is_running;

    void thread1_task();
    void thread2_task();
};

}
#endif
