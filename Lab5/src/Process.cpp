#include "Process.h"
#include <iostream>
#include "MemoryAllocator.h"
#include "Process.h"

Process::Process(const std::string& process_id,
                 std::size_t memory_requirement)
    : process_id_{process_id},
      memory_requirement_{memory_requirement}
{}

void Process::allocate_memory(std::shared_ptr<MemoryAllocator> memory_allocator)
{
    try {
        std::size_t allocated_address = memory_allocator->allocate(process_id_, memory_requirement_);
        std::cout << "Memory allocated for process_id: " << process_id_ << std::endl;
        std::cout << "Starting address: " << allocated_address << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Memory allocation failed for process_id: " << process_id_ << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void Process::deallocate_memory(std::shared_ptr<MemoryAllocator> memory_allocator)
{
    try {
        memory_allocator->deallocate(process_id_);
        std::cout << "Memory deallocated for process_id: " << process_id_ << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Memory deallocation failed for process_id: " << process_id_ << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
    }
}
