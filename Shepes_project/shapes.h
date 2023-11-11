#pragma once

#include <cmath>
#include <stdexcept>
#include <iostream>
//======
//1.Support a few types of 3D geometric curves – circles, ellipses and 3D helixes

// Exception , Curves must be physically correct (e.g. radii must be positive).
class ParameterException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

struct Point {
    Point() = default;
    Point(double x, double y, double z)
        : x(x)
        , y(y)
        , z(z)
    {
    }
    double x = 0;
    double y = 0;
    double z = 0;
};

std::ostream& operator<<(std::ostream& output, Point point) {
    return output << "x="<< point.x << " y=" << point.y << " z=" << point.z << std::endl;
}

class Shape{
public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual Point GetPoint(double t) const = 0;
    virtual Point GetDerivative(double t) const = 0;
    virtual std::string GetType() const = 0;
    virtual double GetRadius() const {
        return 0;
    }
};

class Circle : public Shape {
public:
    explicit Circle(double radius)
    { if ( radius <= 0 ){
            throw (ParameterException("invalid parameter circle"));
        }
        radius_ = radius;
    }
    Point GetPoint(double t) const override {
        return Point{radius_ * std::cos(t), radius_ * std::sin(t), 0};
    }
    Point GetDerivative(double t) const override {
        return Point{-1 * radius_ * std::sin(t), radius_ * std::cos(t), 0};
    }
    std::string GetType() const override {
        return type_;
    }
    double GetRadius() const override {
        return radius_;
    }

private:
    double radius_;
    std::string type_ = "circle";
};

class Ellipse : public Shape {
public:
    explicit Ellipse(double radius_x, double radius_y)
    { if ( radius_x <= 0 || radius_y <= 0 ){
            throw (ParameterException("invalid parameter ellipse"));
        }
        radius_x_ = radius_x;
        radius_y_ = radius_y;
    }
    Point GetPoint(double t) const override {
        return Point{radius_x_ * std::cos(t), radius_y_ * std::sin(t), 0};
    }
    Point GetDerivative(double t) const override {
        return Point{-1 * radius_x_ * std::sin(t), radius_y_ * std::cos(t), 0};
    }
    std::string GetType() const override {
        return type_;
    }

private:
    double radius_x_;
    double radius_y_;
    std::string type_ = "ellipse";
};

class Helix : public Shape {
public:
    explicit Helix(double radius, double step)
    { if ( radius <= 0 || step <= 0 ){
            throw (ParameterException("invalid parameter helix"));
        }
        radius_ = radius;
        step_ = step /(2 * M_PI);
    }
    Point GetPoint(double t) const override {
        return Point{radius_ * std::cos(t), radius_ * std::sin(t), step_ * t};
    }
    Point GetDerivative(double t) const override {
        return Point{-1 * radius_ * std::sin(t), radius_ * std::cos(t), step_};
    }
    std::string GetType() const override {
        return type_;
    }

private:
    double radius_;
    double step_;
    std::string type_ = "helix";
};

