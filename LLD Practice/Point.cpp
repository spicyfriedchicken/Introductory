#include <iostream>

struct Point {
    int x_, y_;
    Point() = default;
    Point (int x, int y) : x_(x), y_(y) {}
    Point (const Point&) = default;
    Point (Point&&) = default;

   Point operator+(const Point& other) const {
        return Point(x_ + other.x, y_ + other.y);
   }

    Point operator-(const Point& other) const {
       return Point(x_ - other.x, y_ - other.y);
   }
    bool operator==(const Point& other) const {
        return (other.x == x_ && other.y == y_);
    }

};

Point add(const Point* a, const Point* b) {
    return Point(a->x_ + b->x_, a->y_ + b->y_);
}

Point subtract(const Point* a, const Point* b) {
    return Point(a->x_ - b->x_, a->y_ - b->y_);
}

Point multiply(const Point* a, const Point* b) {
    return Point(a->x_ * b->x_, a->y_ * b->y_);
}

Point divide(const Point* a, const Point* b) {
    if (b->x == 0 || b->y == 0) {
        std::cerr << "Cannot divide by zero!" << std::endl;
        return Point(0,0);
    }
    return Point(a->x_ / b->x_, a->y_ / b->y_);
}

std::ostream& operator<<(std::ostream& os, const Point& other) {
    return os << "(" << other.x << "," << other.y << ")";
}