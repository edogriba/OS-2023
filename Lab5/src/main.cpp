#include "MemoryAllocator.h"
#include "Process.h"

#include <algorithm>
#include <iostream>


void print_layout(const std::string& title, std::shared_ptr<MemoryAllocator> memory_allocator)
{

    std::cout << title << std::endl;
    std::vector<MemoryBlock> memory = memory_allocator->get_memory_layout();
    //    std::sort(memory.begin(),
    //              memory.end(),
    //              [](MemoryBlock a, MemoryBlock b)
    //    {
    //        return a.start_address < b.start_address;
    //    });

    for (const auto& block : memory) {
        std::cout << "[0x" << std::hex << block.start_address << "-" << block.start_address + block.size - 1 << "] "
                  << block.process_id << " (" << block.size << " bytes)\n";
    }
}

int main()
{
    try {
        // Create memory allocator with a total memory size
        std::shared_ptr<MemoryAllocator> memory_allocator = std::make_shared<MemoryAllocator>(8192);

        // Create processes with their respective memory requirements
        Process process1("Process A", 2048);
        Process process2("Process B", 4096);
        Process process3("Process C", 1024);

        // Allocate memory for processes
        process1.allocate_memory(memory_allocator);
        process2.allocate_memory(memory_allocator);
        process3.allocate_memory(memory_allocator);

        // Print the initial memory layout
        print_layout("Initial Memory Layout:", memory_allocator);

        // Deallocate memory for processes
        process2.deallocate_memory(memory_allocator);

        // Print the initial memory layout
        print_layout("After deallocate process 2:", memory_allocator);

        process3.deallocate_memory(memory_allocator);

        // Print the updated memory layout
        print_layout("Updated Memory Layout:", memory_allocator);
    }
    catch(std::runtime_error e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

