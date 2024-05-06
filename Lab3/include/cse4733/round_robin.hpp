#ifndef ROUND_ROBIN_HPP
#define ROUND_ROBIN_HPP

#include <process.hpp>

#include <iostream>
#include <memory>
#include <vector>

namespace cse4733 {

class round_robin
{
public:

    /**
     * @brief Execute the shortest_job_first algorithm
     * @param processes Handle to the input processes
     * @param quantum Time quantum for run
     */
    void run(std::vector<std::shared_ptr<cse4733::Process>>& processes, int quantum);
};

} // namespace cse4733

#endif // ROUND_ROBIN_HPP
