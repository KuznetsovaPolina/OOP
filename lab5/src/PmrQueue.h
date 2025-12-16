#pragma once
#include <memory_resource>
#include <iterator>
#include <cstddef>
#include <utility>

template<class T>
class PmrQueue {
private:
    struct Node {
        T value;
        Node* next{nullptr};

        Node(const T& v) : value(v), next(nullptr) {}
        Node(T&& v) : value(std::move(v)), next(nullptr) {}
    };

    using allocator_type = std::pmr::polymorphic_allocator<Node>;

    allocator_type alloc_;
    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::size_t size_{0};

public:
    class iterator {
        Node* current_ = nullptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator() = default;
        explicit iterator(Node* n) : current_(n) {}

        reference operator*() const { return current_->value; }
        pointer   operator->() const { return &current_->value; }

        iterator& operator++() {
            if (current_) current_ = current_->next;
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const { return current_ == other.current_; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    class const_iterator {
        const Node* current_ = nullptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() = default;
        explicit const_iterator(const Node* n) : current_(n) {}

        reference operator*() const { return current_->value; }
        pointer   operator->() const { return &current_->value; }

        const_iterator& operator++() {
            if (current_) current_ = current_->next;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const { return current_ == other.current_; }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }
    };

    explicit PmrQueue(std::pmr::memory_resource* res = std::pmr::get_default_resource())
        : alloc_(res) {}

    PmrQueue(const PmrQueue& other)
        : alloc_(other.alloc_) {
        for (Node* n = other.head_; n != nullptr; n = n->next) {
            push(n->value);
        }
    }

    PmrQueue(PmrQueue&& other) noexcept
        : alloc_(other.alloc_), head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    PmrQueue& operator=(const PmrQueue& other) {
        if (this != &other) {
            clear();
            alloc_ = other.alloc_;
            for (Node* n = other.head_; n != nullptr; n = n->next) {
                push(n->value);
            }
        }
        return *this;
    }

    PmrQueue& operator=(PmrQueue&& other) noexcept {
        if (this != &other) {
            clear();
            alloc_ = other.alloc_;
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~PmrQueue() {
        clear();
    }

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    T& front() { return head_->value; }
    const T& front() const { return head_->value; }

    T& back() { return tail_->value; }
    const T& back() const { return tail_->value; }

    void push(const T& v) {
        Node* n = alloc_.allocate(1);
        alloc_.construct(n, v);
        if (!tail_) {
            head_ = tail_ = n;
        } else {
            tail_->next = n;
            tail_ = n;
        }
        ++size_;
    }

    void push(T&& v) {
        Node* n = alloc_.allocate(1);
        alloc_.construct(n, std::move(v));
        if (!tail_) {
            head_ = tail_ = n;
        } else {
            tail_->next = n;
            tail_ = n;
        }
        ++size_;
    }

    void pop() {
        if (!head_) return;
        Node* n = head_;
        head_ = head_->next;
        if (!head_) tail_ = nullptr;
        alloc_.destroy(n);
        alloc_.deallocate(n, 1);
        --size_;
    }

    void clear() {
        while (head_) {
            pop();
        }
    }

    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(nullptr); }

    const_iterator begin() const { return const_iterator(head_); }
    const_iterator end() const { return const_iterator(nullptr); }

    const_iterator cbegin() const { return const_iterator(head_); }
    const_iterator cend() const { return const_iterator(nullptr); }

    bool operator==(const PmrQueue& other) const {
        if (size_ != other.size_) return false;
        auto it1 = begin();
        auto it2 = other.begin();
        for (; it1 != end() && it2 != other.end(); ++it1, ++it2) {
            if (!(*it1 == *it2)) return false;
        }
        return true;
    }

    bool operator!=(const PmrQueue& other) const {
        return !(*this == other);
    }
};
