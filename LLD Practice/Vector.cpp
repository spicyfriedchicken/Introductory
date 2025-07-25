//
// Created by Oscar Abreu on 7/22/25.
//
#pragma once
#include <stdexcept>  // for std::out_of_range
#include <iostream>


class Vector {
private:
    unsigned char* data_; // Because this is a raw pointer, we don't need std::move.
    size_t size_;
public:
    Vector() = delete;
    Vector(unsigned char* data, size_t size) : data_(data), size_(size) {}

    ~Vector() {
        delete[] data_;
    }

    Vector (const Vector& other) : size_(other.size_) {
        data_ = new unsigned char[size_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        delete[] data_;
        size_ = other.size_;
        data_ = new unsigned char[size_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;  // Self-assignment check
        delete[] data_;                    // Clean up existing data!
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
        return *this;                      // Return reference to self
    }

    const unsigned char& operator[](size_t idx) const {
        if (idx >= size_) {
            throw std::out_of_range("Index out of bounds");
        }

       return data_[idx];
    }

     unsigned char& operator[](size_t idx) {
        if (idx >= size_) {
            throw std::out_of_range("Index out of bounds");
        }

        return data_[idx];
    }

    size_t size() const { return size_; }
    unsigned char* data() { return data_; }
    const unsigned char* data() const { return data_; }

};
