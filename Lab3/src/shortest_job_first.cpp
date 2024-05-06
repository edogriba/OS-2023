#include "shortest_job_first.hpp"

#include<algorithm>

namespace cse4733 {


// Comparator function for SJF scheduling
bool shortest_job_first::operator()(const std::shared_ptr<cse4733::Process>& a,
                                    const std::shared_ptr<cse4733::Process>& b) {
    return a->get_burst_time() < b->get_burst_time();
}

void shortest_job_first::run(std::vector<std::shared_ptr<cse4733::Process>>& processes)
{
    int total_waiting = 0;
    int total_turnaround = 0;
    int completion_time = 0;
    int latest_arrival = 0;
    int time;

     // TODO:
    // Step 1: Sort processes from shortest to longest
    std::sort(processes.begin(),
              processes.end(),
              shortest_job_first());

    // Step 2: Find the highest arrival time for the processes
    
    int first = 1;
    for (auto item : processes) {
        if (first == 1) {
            latest_arrival = item->get_arrival_time();
            first = 0;
        }
        else {
            if (latest_arrival < item->get_arrival_time()) {
                latest_arrival = item->get_arrival_time(); 
            }
        }
    }
    for (auto item : processes) {
        item->set_arrival_time(latest_arrival+1); //         Set arrival time for all processes to highest arrival time plus one
        }
    time = latest_arrival+1;
    for (auto item: processes) { 
        item->set_completion_time(time+item->get_burst_time());
        time = item->get_completion_time();
        completion_time = item->get_completion_time();
        item->set_waiting_time(item->get_completion_time()-item->get_burst_time()-item->get_arrival_time());
        total_waiting += item->get_waiting_time();
        item->set_turnaround_time(item->get_completion_time()-item->get_arrival_time());
        total_turnaround += item->get_turnaround_time();
    }
    std::cout << "SJF Scheduling:" << std::endl
              << "   Process ID\tCompletion Time\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time" << std::endl;
    for (auto item : processes)
    {
        std::cout << "  " << *item << std::endl;
    }
    std::cout << "  Average waiting time (tics): " << total_waiting / processes.size() << std::endl;
    std::cout << "  Average turnaround time (tics): " << total_turnaround / processes.size() << std::endl << std::endl;
}

}

