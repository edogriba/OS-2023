#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>

namespace cse4733 {

// Process struct
class Process {
private:

    int m_pid;    // Process ID
    int m_burst;  // Burst time
    int m_arrival; // Arrival time
    int m_remaining;  // Remaining time
    int m_turnaround; // Turnaround time
    int m_waiting;    // Waiting time
    int m_completion_time; // Completion time

public:

    /**
     * @brief Process
     * @param pid Unique identifier for process given my operating system.
     * @param burst Burst time value for the process.
     * @param arrival Arrival time value for the process.
     */
    Process(int pid, int burst, int arrival);

    /**
     * Get the unique identifier.
     * @return Integer value for unique identifier.
     */
    int get_pid() const;

    /**
     * Get the burst time for the process.
     * @return Value of the burst time.
     */
    int get_burst_time() const;

    /**
     * Get the arrival time for the process.
     * @param time Value of the arrival time.
     */
    void set_arrival_time(int time);

    /**
     * Get the arrival time for the process.
     * @return Value of the arrival time.
     */
    int get_arrival_time() const;

    /**
     * Get the remaining time for the process.
     * @return Value of the remaining time.
     */
    int get_remaining_time() const;

    /**
     * Set the remaining time for the process.
     * @return Value of the remaining time.
     */
    void set_remaining_time(int time);

    /**
     * Get the turnaround time for the process.
     * @return Value of the turnaround time.
     */
    int get_turnaround_time() const;

    /**
     * Set the turnaround time for the process.
     * @param time Value of the turnaround time.
     */
    void set_turnaround_time(int time);

    /**
     * Get the waiting time for the process.
     * @return Value of the waiting time.
     */
    int get_waiting_time() const;

    /**
     * Set the waiting time for the process.
     * @param time Value of the waiting time
     */
    void set_waiting_time(int time);

    /**
     * Get the completion time for the process.
     * @return Value of the completion time.
     */
    int get_completion_time() const;

    /**
     * Set the completion time for the process.
     * @param time Value of the completion time
     */
    void set_completion_time(int time);
};

std::ostream& operator<< (std::ostream& os, const Process& obj);
} // namespace cse4733

#endif
