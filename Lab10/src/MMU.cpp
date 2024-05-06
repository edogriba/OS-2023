#include <cse4733/MMU.hpp>

#include <iostream>
#include <stdexcept>

namespace cse4733 {

MMU::MMU(int numPages, unsigned int base_address, unsigned int offset) :
    pageTable(numPages, -1),
    tlbHits{0},
    tlbMisses{0},
    m_base_address(base_address),
    m_offset(offset)
{}

void MMU::addEntry(unsigned int virtualAddress, unsigned int physicalAddress)
{
    // Check if the virtual address is valid
    if (virtualAddress < 0 || virtualAddress >= m_offset) {
        throw std::out_of_range("Virtual address is out of range");
    }

    // Add the entry to the TLB
    tlb.addEntry(virtualAddress, physicalAddress);

    // Also add the entry to the page table
    pageTable[virtualAddress] = physicalAddress;
}

unsigned int MMU::translateAddress(unsigned int virtualAddress) {

    // This function should translate a given virtual address to a physical address:

    if (virtualAddress > m_offset ) { // Check that the address is within the 0 to offset range bounds.
        throw std::out_of_range("Virtual address is out of range");  
    }
    if (tlb.searchTLB(virtualAddress) != -1) {   // Check if the translation is in the TLB (a TLB hit).
        tlbHits++; 
        return tlb.searchTLB(virtualAddress); 
    }
    else {  // If it is not in the TLB (a TLB miss)
        int physicalAddress = -1;
        for (int i=0; i < pageTable.size(); i++ ) {
            if (pageTable[i] == virtualAddress ) {
                physicalAddress = i;
                break;
            }
        }
        if (physicalAddress > -1) { // The physical address is in the page table
            tlb.addEntry(virtualAddress, physicalAddress);
        }
        else { // The physical address is not in the page table
            physicalAddress = virtualAddress + m_base_address;
            tlb.addEntry(virtualAddress, physicalAddress);
            addEntry(virtualAddress, physicalAddress);    
            }
        tlbMisses++;
        return physicalAddress;  // Return the physical address.
    }
    return 0;
    // TODO:
    //
    
    //
     // 1. It should 
    // 
    //
        
    // 2. It should 
    //    a. 
    //       and 

    // 3. :
    //    a. It should look up the physical address in the page table with
    //       the 'virtual address' variable.
    //    b. , it should
    //       1) Set the physical address to the virtual address plus the base address
    //       2) Add the translation to the TLB
    //       3) Store the physical address in the page table
    //    c. Otherwise, , it should
    //       1) Create an entry in the TLB table
    //    d. Increment the count of TLB misses.
    //
    // 4. 
}

double MMU::getHitRatio() {

    //   - Calculate HIT ratio

    float sum = tlbHits + tlbMisses;
    float hitRatio = (float) tlbHits / sum ;
    return hitRatio;
}

double MMU::getMissRatio() {

    //   - Calculate MISS ratio

    float sum = tlbHits + tlbMisses;
    float missesRatio = (float) tlbMisses / sum ;
    return missesRatio;
    }

}  // namespace cse4733

