#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <string>
#include <vector>

struct MemoryBlock {
    std::size_t start_address;
    std::size_t size;
    std::string process_id;
};

class MemoryAllocator {
public:
    MemoryAllocator(std::size_t total_memory_size);

    auto allocate(const std::string& process_id, std::size_t size) -> std::size_t;
    void deallocate(const std::string& process_id);
    auto get_memory_layout() -> std::vector<MemoryBlock>&;

private:
    std::size_t total_memory_size_;
    std::vector<MemoryBlock> memory_blocks_;

    // Helper functions
    void merge_free_blocks();
};

#endif // MEMORY_ALLOCATOR_H

