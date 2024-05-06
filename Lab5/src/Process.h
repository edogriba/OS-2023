#ifndef PROCESS_H
#define PROCESS_H

#include <memory>
#include <string>

class MemoryAllocator;

class Process {
public:
    Process(const std::string& process_id, std::size_t memory_requirement);
    void allocate_memory(std::shared_ptr<MemoryAllocator> memory_allocator);
    void deallocate_memory(std::shared_ptr<MemoryAllocator> memory_allocator);

private:
    std::string process_id_;
    std::size_t memory_requirement_;
};

#endif // PROCESS_H

