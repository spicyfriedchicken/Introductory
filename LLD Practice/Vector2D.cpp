//
// Created by Oscar Abreu on 7/25/25.
//

#include <SDL2.h>

class Vector2D {
private:
    SDL2_FPoint pos_;

public:
    Vector2D() = default;
    Vector2D(float x = 0.0f, float y = 0.0f) {
        pos_.x = x;
        pos_.y = y;
    }
    Vector2D(const SDL2_FPoint point) : pos_(point) {}
    Vector2D& operator=(const Vector2D& vec) {
        if (this != &vec) {
            pos_ = vec.pos_;
        }
        return *this;
    }
    Vector2D(Vector2D&& other) :  x_(std::move(other.x_)), y_(std::move(other.y_)) {}
    Vector2D& operator=(Vector2D&& vec) {
        if (this != &vec) {
            pos_ = vec.pos_;
        }
        return *this;
    }
    Vector2D operator+(const Vector2D& rhs) const {
        return Vector2D(pos_.x + rhs.pos_.x, pos_.y + rhs.pos_.y);
    }

    Vector2D& operator+=(const Vector2D& rhs) {
        pos_.x += rhs.pos_.x;
        pos_.y += rhs.pos_.y;
        return *this;
    }
    Vector2D operator-(const Vector2D& rhs) const {
        return Vector2D(pos_.x - rhs.pos_.x, pos_.y - rhs.pos_.y);
    }

    Vector2D& operator-=(const Vector2D& rhs) {
        pos_.x -= rhs.pos_.x;
        pos_.y -= rhs.pos_.y;
        return *this;
    }

    Vector2D operator*(float scalar) const {
        return Vector2D(pos_.x * scalar, pos_.y * scalar);
    }

    float magnitude() const {
        return std::sqrt(pos_.x * pos_.x + pos_.y * pos_.y);
    }

    Vector2D normalized() const {
        float mag = magnitude();
        if (mag == 0) return *this;
        return *this * (1.0f / mag);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "(" << v.pos_.x << ", " << v.pos_.y << ")";
        return os;
    }

    float x() const { return pos_.x; }
    float y() const { return pos_.y; }
};