#include "round_robin.hpp"

#include<algorithm>
#include<queue>

namespace cse4733 {

void round_robin::run(std::vector<std::shared_ptr<cse4733::Process>>& processes, int quantum)
{
    int n = processes.size();
    int time = 0;
    int total_waiting = 0;
    int total_turnaround = 0;
    std::queue<std::shared_ptr<cse4733::Process>> ready_queue;

    // For all arriving processes in processes list
    //   Add process to ready queue
    //   Remove process from processes list
    // EndFor
    for (auto item : processes)
    {
        ready_queue.push(item);
    }

    // TODO:
    while (ready_queue.size() > 0) { 
        //std::cout << "" << ready_queue.front()->get_burst_time() << "" << std::endl;
        //std::cout << "" << ready_queue.front()->get_remaining_time() << "" << std::endl;
        if (quantum < ready_queue.front()->get_remaining_time()) {
            ready_queue.front()->set_remaining_time(ready_queue.front()->get_remaining_time()-quantum);
            time += quantum;
            ready_queue.push(ready_queue.front());
            ready_queue.pop();
        }
        else {
            time += ready_queue.front()->get_remaining_time();
            ready_queue.front()->set_completion_time(time);
            ready_queue.front()->set_turnaround_time(ready_queue.front()->get_completion_time()-ready_queue.front()->get_arrival_time());
            total_turnaround += ready_queue.front()->get_turnaround_time();
            ready_queue.front()->set_waiting_time(ready_queue.front()->get_completion_time()-(ready_queue.front()->get_arrival_time() + ready_queue.front()->get_burst_time()));
            total_waiting += ready_queue.front()->get_waiting_time();
            ready_queue.pop();
        }
    }
    //
    // Loop until all processes are removed from the ready queue
    //   Get process from ready queue
    //   Execute the process for the quantum or remaining time, whichever is smaller
    //   Add execution time to time
    //   Set the remaining time for the process
    //   If the remaining time for the process is not zero THEN
    //     Add process to the back of the ready queue
    //   Else
    //     Set the completion time for the process
    //     Set the turnaround time for the process
    //     Add turnaround time to turnaround time total
    //     Set the waiting time for the process
    //     Add waiting time to waiting time total
    //   End If
    // End Loop

    std::cout << "Round Robin Scheduling:\n";
    std::cout << "   Process ID\tCompletion Time\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n";
    for (auto obj : processes) {
        std::cout << "  " << *obj << std::endl;
    }
    std::cout << "  Average Waiting Time: " << (double)total_waiting / n << std::endl;
    std::cout << "  Average Turnaround Time: " << (double)total_turnaround / n << std::endl;
}

}

