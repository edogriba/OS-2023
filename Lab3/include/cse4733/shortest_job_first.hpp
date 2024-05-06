#ifndef SHORTEST_JOB_FIRST_HPP
#define SHORTEST_JOB_FIRST_HPP

#include <process.hpp>

#include <iostream>
#include <memory>
#include <vector>

namespace cse4733 {

class shortest_job_first
{
public:

    // Comparator function for SJF scheduling
    bool operator()(const std::shared_ptr<cse4733::Process>& a,
                    const std::shared_ptr<cse4733::Process>& b);

    /**
     * @brief Execute the shortest_job_first algorithm
     */
    void run(std::vector<std::shared_ptr<cse4733::Process>>& processes);
};


} // namespace cse4733

#endif // SHORTEST_JOB_FIRST_HPP
