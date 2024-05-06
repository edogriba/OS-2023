#include <vector>

#include <cse4733/TLB.hpp>

namespace cse4733 {

class MMU {
private:

    /**
     *  A translation-lookaside buffer (TLB) is part of the chip’s
     *  memory-management unit (MMU), and is simply a hardware cache
     *  of popular virtual-to-physical address translations; thus,
     *  a better name would be an address-translation cache.
     */
    TLB tlb;

    /**
     * The page table contains all physical addresses.
     */
    std::vector<int> pageTable;

    /**
     * Number of times the physical address was found in the TLB.
     */
    int tlbHits;

    /**
     * Number of times the physical address was NOT found in the TLB.
     */
    int tlbMisses;

    /**
     * @brief m_base_address Beginning address of the physical memory.
     */
    const unsigned int m_base_address;

    /**
     * @brief m_offset Number of physical memory addresses.
     */
    const unsigned int m_offset;
public:

    /**
     * @brief MMU The memory-management unit (MMU) constructor.
     * @param numPages Number of physical addresses in the system.
     * @param base_address Beginning address of the physical memory.
     * @param offset Number of physical memory addresses.
     */
    MMU(int numPages, unsigned int base_address, unsigned int offset);

    /**
     * @brief translateAddress The MMU searches the TLB for the physical address for the given virtual address.
     * @param virtualAddress Virtual memory address of the memory location.
     * @return The physical memory address of the memory location.
     */
    unsigned int translateAddress(unsigned int virtualAddress);

    /**
     * @brief getHitRatio Retrieve the TLB hit ratio.
     * @return Fractional number representing the TLB hit ratio.
     */
    double getHitRatio();

    /**
     * @brief getMissRatio Retrieve the TLB miss ratio.
     * @return Fractional number representing the TLB miss ratio.
     */
    double getMissRatio();

    /**
     * @brief addEntry Create a memory location within the MMU.
     * @param virtualAddress Virtual memory address of the memory location.
     * @param physicalAddress The physical memory address of the memory location.
     */
    void addEntry(unsigned int virtualAddress, unsigned int physicalAddress);
};

}  // namespace cse4733
