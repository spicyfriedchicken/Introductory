#include <iostream> 
#include <vector>

template <typename T>
class RingBuffer{
public:
    
    size_t size_;
    size_t nextRead;
    size_t lastInsert;
    std::vector<T> data_;
   
    RingBuffer(const RingBuffer&) = delete;
    RingBuffer& operator=(const RingBuffer&) = delete;
    RingBuffer(RingBuffer&&) = delete;
    RingBuffer& operator=(RingBuffer&&) = delete;


    RingBuffer() {
        size_ = 500;
        lastInsert = -1;
        nextRead = 0;
        data_.resize(size_);
    }

    RingBuffer(const vector<T>& data) {
        size_ = data.size();
        nextRead = 0;
        lastInsert = data.size() - 1;
        data_ = data;
    }

    void insert(const T& value) {
        lastInsert = (lastInsert + 1) % size_;
        data_[lastInsert] = value;

        if (nextRead == lastInsert) {
            nextRead = (nextRead + 1) % size_;  // Overwrite oldest
        }
    }

    void erase (size_t idx) {
        if (idx < size_) data_[idx] = T();
    }

    T readNext() const {
        return data_[nextRead]
    }

    size_t capacity() const {
        return size_;
    }

}
