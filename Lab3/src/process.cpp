#include <process.hpp>

#include <iostream>

namespace cse4733 {

Process::Process(int pid, int burst, int arrival)
    : m_pid(pid),
      m_burst(burst),
      m_arrival(arrival),
      m_remaining(burst),
      m_turnaround(0),
      m_waiting(0),
      m_completion_time(0)
{}

int Process::get_pid() const
{
    return m_pid;
}

int Process::get_burst_time() const
{
    return m_burst;
}

void Process::set_arrival_time(int time)
{
    m_arrival = time;
}

int Process::get_arrival_time() const
{
    return m_arrival;
}

int Process::get_remaining_time() const
{
    return m_remaining;
}

void Process::set_remaining_time(int time)
{
    m_remaining = time;
}

int Process::get_turnaround_time() const
{
    return m_turnaround;
}

void Process::set_turnaround_time(int time)
{
    m_turnaround = time;
}

int Process::get_waiting_time() const
{
    return m_waiting;
}

void Process::set_waiting_time(int time)
{
    m_waiting = time;
}

int Process::get_completion_time() const
{
    return m_completion_time;
}

void Process::set_completion_time(int time)
{
    m_completion_time = time;
}

std::ostream& operator<< (std::ostream& os, const Process& obj )
{
    os << obj.get_pid()
       << "\t\t"
       << obj.get_completion_time()
       << "\t\t"
       << obj.get_burst_time()
       << "\t\t"
       << obj.get_arrival_time()
       << "\t\t"
       << obj.get_waiting_time()
       << "\t\t"
       << obj.get_turnaround_time();
    return os;
}

}
