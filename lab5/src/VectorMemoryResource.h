#pragma once
#include <memory_resource>
#include <vector>
#include <cstddef>
#include <new>

class VectorMemoryResource : public std::pmr::memory_resource {
    struct Block {
        void*  ptr;
        std::size_t size;
        std::size_t alignment;
        bool   free;
    };

    std::vector<Block> blocks_;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        for (auto& b : blocks_) {
            if (b.free && b.size >= bytes && b.alignment >= alignment) {
                b.free = false;
                return b.ptr;
            }
        }

        void* p = nullptr;
    #if defined(__cpp_aligned_new)
        if (alignment > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
            p = ::operator new(bytes, std::align_val_t(alignment));
        } else {
            p = ::operator new(bytes);
        }
    #else
        (void)alignment;
        p = ::operator new(bytes);
    #endif

        blocks_.push_back(Block{p, bytes, alignment, false});
        return p;
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        (void)bytes;
        (void)alignment;
        for (auto& b : blocks_) {
            if (b.ptr == p) {
                b.free = true;
                return;
            }
        }
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

public:
    ~VectorMemoryResource() override {
        for (auto& b : blocks_) {
        #if defined(__cpp_aligned_new)
            if (b.alignment > __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
                ::operator delete(b.ptr, std::align_val_t(b.alignment));
            } else {
                ::operator delete(b.ptr);
            }
        #else
            (void)b.alignment;
            ::operator delete(b.ptr);
        #endif
        }
    }
};
