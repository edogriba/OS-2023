#include <cse4733/TLB.hpp>

namespace cse4733 {

void TLB::addEntry(unsigned int virtualAddress, unsigned int physicalAddress) {
    entries.emplace(virtualAddress, physicalAddress);
}

unsigned int TLB::searchTLB(unsigned int virtualAddress) {
    unsigned int physicalAddress = -1;
    auto iterator = entries.find(virtualAddress);
    if (iterator != entries.end())
    {
        physicalAddress = iterator->second;
    }
    return physicalAddress;
}

}  // namespace cse4733

