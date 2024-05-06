#include "first_come_first_served.hpp"

#include <iostream>

namespace cse4733 {

void first_come_first_served::run(std::vector<std::shared_ptr<cse4733::Process>>& processes)
{
    int completion_time = 0;
    int total_waiting = 0;
    int total_turnaround = 0;

    
    // TODO:
    //
    // For all processes
    //   Add the process burst time to completion time (how long to run process)
    //   Determine the amount of time it took to finish process execution
    //      turnaround time = completion time - arrival time
    //   Set the process turnaround time
    //   Add turnaround time to the total turnaround time
    //
    //   Determine the amount of time the process waited for execution.
    //      waiting time = completion time - (arrival time + burst time)
    //   Set the process waiting time
    //   Add waiting time to the total waiting time

    for (auto item : processes) {
            // std::cout << "  " << item->get_pid() ;
            
            completion_time += item->get_burst_time();
            item->set_turnaround_time(completion_time - item->get_arrival_time());
            total_turnaround += item->get_turnaround_time();
            item->set_waiting_time(completion_time - (item->get_arrival_time() + item->get_burst_time()));
            total_waiting += item->get_waiting_time();
            item->set_completion_time(item->get_arrival_time()+item->get_burst_time()+item->get_waiting_time());
            // std::cout << endl;
    }

    std::cout << "FCFS Scheduling:" << std::endl
              << "  Process ID\tCompletion Time\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time" << std::endl;

    for (auto item : processes)
    {
        std::cout << "  " << *item << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "  Average waiting time (tics): " << total_waiting / processes.size() << std::endl;
    std::cout << "  Average turnaround time (tics): " << total_turnaround / processes.size() << std::endl << std::endl;
}

}

