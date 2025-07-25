#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdint>
#include <type_traits>

class IntType {
public:
    // i regret adding this many types
    enum class Type {INT8, INT16, INT32, INT64, UINT8, UINT16, UINT32, UINT64, NONE};

    IntType() : type_(Type::NONE) {}
    IntType(int8_t i) : type_(Type::INT8) {value_.int8 = i}
    IntType(int16_t i) : type_(Type::INT16) {value_.int16 = i}
    IntType(int32_t i) : type_(Type::INT32) {value_.int32 = i}
    IntType(int64_t i) : type_(Type::INT64) {value_.int64 = i}
    IntType(uint8_t i) : type_(Type::UINT8) {value_.uint8 = i}
    IntType(uint16_t i) : type_(Type::UINT16) {value_.uint16 = i}
    IntType(uint32_t i) : type_(Type::UINT32) {value_.uint32 = i}
    IntType(uint64_t i) : type_(Type::UINT64) {value_.uint64 = i}

    ~IntType() {
        reset();
    }

    // copy constructor
    IntType(const IntType& other) {
        type_ = other.type_;
        switch (type_) {
            case Type::INT8:   value_.int8 = other.value_.int8; break;
            case Type::INT16:  value_.int16 = other.value_.int16; break;
            case Type::INT32:  value_.int32 = other.value_.int32; break;
            case Type::INT64:  value_.int64 = other.value_.int64; break;
            case Type::UINT8:  value_.uint8 = other.value_.uint8; break;
            case Type::UINT16: value_.uint16 = other.value_.uint16; break;
            case Type::UINT32: value_.uint32 = other.value_.uint32; break;
            case Type::UINT64: value_.uint64 = other.value_.uint64; break;
            default: break;
        }
    }

    IntType& operator=(const IntType& other) {
        if (this != &other) {
            reset();
            type_ = other.type_;
            switch (type_) {
                case Type::INT8:   value_.int8 = other.value_.int8; break;
                case Type::INT16:  value_.int16 = other.value_.int16; break;
                case Type::INT32:  value_.int32 = other.value_.int32; break;
                case Type::INT64:  value_.int64 = other.value_.int64; break;
                case Type::UINT8:  value_.uint8 = other.value_.uint8; break;
                case Type::UINT16: value_.uint16 = other.value_.uint16; break;
                case Type::UINT32: value_.uint32 = other.value_.uint32; break;
                case Type::UINT64: value_.uint64 = other.value_.uint64; break;
                default: break;
            }
        }
        return *this;
    }

    template<typename T>
    void set(T val) {
        reset();
        if constexpr (std::is_same_v<T, int8_t>) {
            type_ = Type::INT8;
            value_.int8 = val;
        } else if constexpr (std::is_same_v<T, int16_t>) {
            type_ = Type::INT16;
            value_.int16 = val;
        } else if constexpr (std::is_same_v<T, int32_t>) {
            type_ = Type::INT32;
            value_.int32 = val;
        } else if constexpr (std::is_same_v<T, int64_t>) {
            type_ = Type::INT64;
            value_.int64 = val;
        } else if constexpr (std::is_same_v<T, uint8_t>) {
            type_ = Type::UINT8;
            value_.uint8 = val;
        } else if constexpr (std::is_same_v<T, uint16_t>) {
            type_ = Type::UINT16;
            value_.uint16 = val;
        } else if constexpr (std::is_same_v<T, uint32_t>) {
            type_ = Type::UINT32;
            value_.uint32 = val;
        } else if constexpr (std::is_same_v<T, uint64_t>) {
            type_ = Type::UINT64;
            value_.uint64 = val;
        } else {
            static_assert(sizeof(T) == 0, "Unsupported type in IntType::set()");
        }
    }

    template<typename T>
    T get() const {
        if constexpr (std::is_same_v<T, int8_t>) {
            if (type_ != Type::INT8) throw std::runtime_error("Type is not int8_t");
            return value_.int8;
        } else if constexpr (std::is_same_v<T, int16_t>) {
            if (type_ != Type::INT16) throw std::runtime_error("Type is not int16_t");
            return value_.int16;
        } else if constexpr (std::is_same_v<T, int32_t>) {
            if (type_ != Type::INT32) throw std::runtime_error("Type is not int32_t");
            return value_.int32;
        } else if constexpr (std::is_same_v<T, int64_t>) {
            if (type_ != Type::INT64) throw std::runtime_error("Type is not int64_t");
            return value_.int64;
        } else if constexpr (std::is_same_v<T, uint8_t>) {
            if (type_ != Type::UINT8) throw std::runtime_error("Type is not uint8_t");
            return value_.uint8;
        } else if constexpr (std::is_same_v<T, uint16_t>) {
            if (type_ != Type::UINT16) throw std::runtime_error("Type is not uint16_t");
            return value_.uint16;
        } else if constexpr (std::is_same_v<T, uint32_t>) {
            if (type_ != Type::UINT32) throw std::runtime_error("Type is not uint32_t");
            return value_.uint32;
        } else if constexpr (std::is_same_v<T, uint64_t>) {
            if (type_ != Type::UINT64) throw std::runtime_error("Type is not uint64_t");
            return value_.uint64;
        } else {
            static_assert(sizeof(T) == 0, "Unsupported type in get<T>()");
        }
    }

private:
    union {
        uint8_t uint8;
        uint16_t uint16;
        uint32_t uint32;
        uint64_t uint64;
        int8_t int8;
        int16_t int16;
        int32_t int32;
        int64_t int64;
    } value_;
    Type type_;

    void reset() {
        type_ = Type::NONE;
    }

};