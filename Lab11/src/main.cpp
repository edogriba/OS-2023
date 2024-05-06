#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <map>
#include <boost/program_options.hpp>

const unsigned int PAGE_SIZE = 4096; // Page size in bytes
const unsigned int PAGE_TABLE_SIZE = 1024; // Number of entries in page table
const unsigned int PAGE_DIRECTORY_SIZE = 1024; // Number of entries in page directory
const unsigned int PAGE_TABLE_MASK = 0x0FFC00;
const unsigned int PAGE_TABLE_BIT_SHIFT = 12;
const unsigned int PAGE_DIRECTORY_MASK = 0xFFC00000;
const unsigned int PAGE_DIRECTORY_BIT_SHIFT = 22;
const unsigned int PAGE_OFFSET_MASK = 0x0FFF;
const unsigned int PAGE_FRAME_NUMBER_SHIFT = 22;

// Structure representing a Page Table Entry (PTE)
struct page_table_entry {
    bool valid; // Valid bit
    unsigned int page_frame_number; // Page Frame Number (PFN)
};

// Function to simulate page table lookup
/**
 *
 * A virtual address can be further broken down into individual bits,
 * each representing a specific component of the address. Here's the
 * bit breakdown of a virtual address:
 *
 *--------------------------------------------------------------
 * Assuming a 32-bit virtual address space:
 *
 * The highest-order bits represent the page directory index.
 * The next set of bits represents the page table index.
 * The remaining bits represent the page offset.
 * Here's an example breakdown of a 32-bit virtual address:
 *
 * 31            22            12                0
 * +--------------+--------------+----------------+
 * | Page Dir.    | Page Table   | Page Offset    |
 * | Index        | Index        |                |
 * +--------------+--------------+----------------+
 *
 */
void pageTableLookup(const std::map<std::pair<unsigned int, unsigned int>, page_table_entry> & pageTable,
                     unsigned int virtualAddress) {

    // 1. Extract the page table index, page directory index, and page offset from the
    //    virtual address using appropriate bit masks and shifts.
    //
    // 2. Create a key pair using the page directory index and page table index.
    // 3. Retrieve the corresponding page table entry from the page table data structure using the key.
    // 4. Check if the page table entry is valid and handle page faults accordingly.
    // 5. Calculate the physical address using the page frame number times page size plus page offset.
    unsigned int pageTableIndex = 0;
    unsigned int pageDirectoryIndex = 0;
    unsigned int pageOffset = 0;
    unsigned int physicalAddress = 0;
    
    pageDirectoryIndex = (virtualAddress & PAGE_DIRECTORY_MASK) >> PAGE_DIRECTORY_BIT_SHIFT;
    pageTableIndex = (virtualAddress & PAGE_TABLE_MASK) >> PAGE_TABLE_BIT_SHIFT;
    pageOffset = (virtualAddress & PAGE_OFFSET_MASK);
    
    std::pair key_pair = std::make_pair(pageDirectoryIndex, pageTableIndex);
    
    auto it = pageTable.find(key_pair);

    if (it == pageTable.end()){
        std::cout << "Page table entry not found" << std::endl;
        return;
    }
    else if (it->second.valid == false) {
        std::cout << "Page table entry not valid" << std::endl;
        return;
    }
    physicalAddress = pageOffset + (it->second.page_frame_number  * PAGE_SIZE);
    
    std::cout << "Virtual Address: 0x" << std::hex << virtualAddress << "(" << std::dec << virtualAddress << ")" << std::endl
              << "  Page Directory Index:.. 0x" << std::hex << pageDirectoryIndex << " (" << std::dec << pageDirectoryIndex << ")" << std::endl
              << "  Page Table Index:...... 0x" << std::hex << pageTableIndex << " (" << std::dec << pageTableIndex << ")" <<std::endl
              << "  Page offset:........... 0x" << std::hex << pageOffset << " (" << std::dec << pageOffset << ")" << std::endl
              << std::endl;


    std::cout << "Physical Address: 0x" << std::hex << physicalAddress << "\n";
}

int main(int argc, char* argv[]) {
    // Declare the supported command-line options
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("num-addresses,n", boost::program_options::value<int>(), "set the number of virtual addresses");

    // Parse the command-line options
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    // Display help message if requested or if the number of virtual addresses is not provided
    if (vm.count("help") || !vm.count("num-addresses")) {
        std::cout << desc << "\n";
        return 1;
    }

    int numAddresses = vm["num-addresses"].as<int>();

    // Create and initialize the page table
    std::map<std::pair<unsigned int, unsigned int>, page_table_entry> pageTable;

    // Initialize the page table entries
    for (unsigned int i = 0; i < PAGE_DIRECTORY_SIZE; ++i) {
        for (unsigned int j = 0; j < PAGE_TABLE_SIZE; ++j) {
            std::pair<unsigned int, unsigned int> key(i, j);
            pageTable[key] = { true, j }; // Set valid bit to true and assign page frame number
        }
    }

    // Generate and simulate page table lookup for virtual addresses
    for (int i = 0; i < numAddresses; ++i) {
        unsigned long long virtualAddress = rand() % (static_cast<unsigned long long>(PAGE_SIZE) * PAGE_TABLE_SIZE * PAGE_DIRECTORY_SIZE);
        pageTableLookup(pageTable, virtualAddress);
    }

    return 0;
}
