//
// Created by Oscar Abreu on 7/22/25.
//
#pragma once

class Rectangle {
public:

    Rectangle() = default;
    Rectangle(double width, double height) : width_(width), height_(height) {}

    double getWidth() const {return width_;}
    double getHeight() const {return height_;}

    double area() const {return width_ * height_;}
    double perimeter() const {return width_*2 + height_*2;}

private:
    double width_ = 0.0, height_ = 0.0;
};
