#ifndef FIRST_COME_FIRST_SERVED_HPP
#define FIRST_COME_FIRST_SERVED_HPP

#include <process.hpp>

#include <iostream>
#include <memory>
#include <vector>

namespace cse4733 {

class first_come_first_served
{
public:

    /**
     * @brief Execute the first_come_first_served algorithm
     */
    void run(std::vector<std::shared_ptr<cse4733::Process>>& processes);
};

} // namespace cse4733

#endif // FIRST_COME_FIRST_SERVED_HPP
