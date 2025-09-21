#pragma once
#include <ostream>
#include <cmath>

    class Point2D {
    public:
        constexpr Point2D() noexcept = default;
        constexpr Point2D(double x, double y) noexcept : x_(x), y_(y) {}

        constexpr Point2D& operator=(const Point2D&) noexcept = default;
        constexpr Point2D(const Point2D&) noexcept = default;
        constexpr Point2D(Point2D&&) noexcept = default;
        constexpr Point2D& operator=(Point2D&&) noexcept = default;
        ~Point2D() = default;


        [[nodiscard]] double distance_to_euclidean(const Point2D& a) const noexcept {
            return std::hypot(a.x_ - x_, a.y_ - y_);
        }
        constexpr double x() const noexcept { return x_; }
        constexpr double y() const noexcept { return y_; }

    private:
        double x_{0.0}, y_{0.0};
    };


    inline double distance_to_euclidean(const Point2D& a, const Point2D& b) noexcept {
            return a.distance_to_euclidean(b);
    }
    inline std::ostream& operator<<(std::ostream& os, const Point2D& rhs) {
        return os << "(" << rhs.x_ << "," << rhs.y_ << ")\n";
    }
    constexpr Point2D operator+(const Point2D& a, const Point2D& b) {
        return {a.x() + b.x(), a.y() + b.y()};
    }
    constexpr Point2D operator-(const Point2D& a, const Point2D& b) {
        return {a.x() - b.x(), a.y() - b.y()};
    }
    constexpr Point2D operator==(const Point2D& a, const Point2D& b) {
        return {a.x() == b.x() && a.y() == b.y()};
    }
    constexpr bool operator<(const Point2D& a, const Point2D& b) {
        return (a.x() < b.x()) || (a.x() == b.x() && a.y() < b.y());
    }
    constexpr bool operator!=(const Point2D& a, const Point2D& b) noexcept { return !(a == b); }
    constexpr bool operator>(const Point2D& a, const Point2D& b) noexcept  { return b < a; }
    constexpr bool operator<=(const Point2D& a, const Point2D& b) noexcept { return !(b < a); }
    constexpr bool operator>=(const Point2D& a, const Point2D& b) noexcept { return !(a < b); }
