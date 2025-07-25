#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Stack {
private:
    std::vector<T> data_;
    size_t curr_offset_;

    void resize() {
        size_t new_capacity = data_.capacity() == 0 ? 2 : data_.capacity() * 2;
        data_.reserve(new_capacity);
    }

    void downsize() {
        if (data_.capacity() >= 4 * curr_offset_) {
            std::vector<T> new_data;
            new_data.reserve(std::max<size_t>(2, 2 * curr_offset_));
            for (size_t i = 0; i < curr_offset_; ++i)
                new_data.emplace_back(std::move(data_[i]));
            data_ = std::move(new_data);
        }
    }

public:
    Stack() : curr_offset_(0) {
        data_.reserve(2);
    }

    Stack(const Stack&) = delete;
    Stack(Stack&&) = default;
    Stack& operator=(Stack&&) = default;
    ~Stack() = default;

    template <typename... Args>
    void emplace_push(Args&&... args) {
        if (curr_offset_ >= data_.capacity()) resize();
        data_.emplace_back(std::forward<Args>(args)...);
        ++curr_offset_;
    }

    void push(const T& val) {
        if (curr_offset_ >= data_.capacity()) resize();
        if (curr_offset_ < data_.size())
            data_[curr_offset_++] = val;
        else {
            data_.emplace_back(val);
            ++curr_offset_;
        }
    }

    void push(T&& val) {
        if (curr_offset_ >= data_.capacity()) resize();
        if (curr_offset_ < data_.size())
            data_[curr_offset_++] = std::move(val);
        else {
            data_.emplace_back(std::move(val));
            ++curr_offset_;
        }
    }

    T pop() {
        if (curr_offset_ == 0) throw std::runtime_error("Stack underflow");
        T res = std::move(data_[--curr_offset_]);
        downsize();
        return res;
    }

    T& top() {
        if (curr_offset_ == 0) throw std::runtime_error("Stack empty");
        return data_[curr_offset_ - 1];
    }

    const T& top() const {
        if (curr_offset_ == 0) throw std::runtime_error("Stack empty");
        return data_[curr_offset_ - 1];
    }

    size_t size() const { return curr_offset_; }
    size_t capacity() const { return data_.capacity(); }
    bool empty() const { return curr_offset_ == 0; }
};
