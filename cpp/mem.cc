#include <iostream>
#include <vector>
#include <cstdlib>
class MemoryPool {

public:
    MemoryPool(int size) : size_(size) {

    }

    void* allocate() {
        void *res = nullptr;
        if(!vector_.empty()) {
            res = vector_.back();
            vector_.pop_back();
        }
        else {
            res = malloc(size_);
            if(res == nullptr) {
                // TODO: failed memory
            }
        }
        return res;
    }

    void deallocate(void *pointer) {
        vector_.push_back(pointer);
        pointer = nullptr;
    }

    ~MemoryPool() {
        for(auto &pointer : vector_) {
            free(pointer);
            pointer = nullptr;
        }
    }
private:
    std::vector<void*> vector_;
    int size_;
};