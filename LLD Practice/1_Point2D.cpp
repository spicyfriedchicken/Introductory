#include <iostream>

struct Point2D {
public:
    Point2D() : x_{0.0f}, y_{0.0f} {}

    Point2D(float x, float y) : x_(x), y_(y) {}
    Point2D(const Point2D& other) : x_{other.x_}, y_{other.y_} {}
    Point2D& operator=(const Point2D& other) {
        if (&other == this) return *this;
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }
    Point2D(Point2D&& other) noexcept : x_(other.x_), y_(other.y_) {}
    Point2D& operator=(Point2D&& other) noexcept {
        if (&other == this) return *this;
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }

    [[nodiscard]] constexpr float x() const noexcept { return x_; }
    [[nodiscard]] constexpr float y() const noexcept { return y_; }
    constexpr void setX(float x) noexcept { x_ = x; }
    constexpr void setY(float y) noexcept { y_ = y; }

    [[nodiscard]] float norm() const noexcept { return std::sqrt(x_*x_ + y_*y_); }

    friend constexpr bool operator==(const Point2D& a, const Point2D& b) noexcept {
        return a.x_ == b.x_ && a.y_ == b.y_;
    }
    friend constexpr std::ostream& operator==(std::ostream& os, const Point2D& a) noexcept {
        return os << "(" << a.x_ << "," << a.y_ << ")" << std::endl;
    }
    ~Point2D() = default;

private:
    float x_{0.0f};
    float y_{0.0f};
};
