#include <algorithm>
#include <iostream>
#include <vector>

#include "MemoryAllocator.h"

MemoryAllocator::MemoryAllocator(std::size_t total_memory_size)
    : total_memory_size_(total_memory_size)
{
    // Initialize memory with a single block representing free memory
    memory_blocks_.push_back({0, total_memory_size_, "Free Memory"});
}

std::size_t MemoryAllocator::allocate(const std::string& process_id, std::size_t size)
{
   // TODO: Implement memory allocation logic
    int i=0;
    std::size_t allocated_address;
    for (auto itr = memory_blocks_.begin(); itr != memory_blocks_.end(); itr++) {  // Find a suitable memory block to allocate
        if ((itr->process_id.compare("Free Memory") == 0) && itr->size >= size) { // Allocate memory within the block
            allocated_address = itr->start_address; 
            itr->start_address += size;
            itr->size -= size;
            if (itr->size == 0) {
                memory_blocks_.erase(memory_blocks_.begin()+i); // Remove the block if it becomes empty
            }
            memory_blocks_.push_back({allocated_address, size, process_id});    // Add the allocated memory block
            return allocated_address;  
        }
        i++;
    }
    // No suitable memory block found, throw an exception
    throw std::runtime_error("Memory allocation failed for process_id: " + process_id);
}

void MemoryAllocator::deallocate(const std::string& process_id)
{
    // TODO: Implement memory deallocation logic
    for (auto itr = memory_blocks_.begin(); itr != memory_blocks_.end(); itr++) {
        if (itr->process_id.compare(process_id) == 0) {
            itr->process_id = "Free Memory";
            merge_free_blocks();
            return;
        }
        
    }
    // No memory block found for the process ID, throw an exception
    throw std::runtime_error("Memory deallocation failed for process_id: " + process_id);
}

void MemoryAllocator::merge_free_blocks()
{

   for (auto itr = memory_blocks_.begin(); itr != memory_blocks_.end(); itr++) {
        if (itr->process_id.compare("Free Memory") == 0 ) {
            auto next_itr = itr+1;
            if ( next_itr->process_id.compare("Free Memory") == 0 && next_itr != memory_blocks_.end()) {
                itr->size += next_itr->size;
                memory_blocks_.erase(next_itr);           
            }
        }
    } 
}
std::vector<MemoryBlock>& MemoryAllocator::get_memory_layout()
{
    return memory_blocks_;
}


