#ifndef Vector_hpp
#define Vector_hpp

#include <cmath>
#include <iostream>


class Vector {
public:
    Vector(float x, float y)
    : x(x), y(y) {};
    
    explicit Vector(float value = 0)
        : x(value), y(value) {};
    
    float LengthVector() const;
    float LengthQuad() const;
    float Scalar(const Vector& v) const;
    Vector& Normalize();

    Vector& operator*=(float scalar);
    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    Vector operator-() const;

    bool operator==(const Vector& v) const;
    bool operator()(const Vector& left, const Vector& right) const;
    Vector& operator=(const Vector& v);
    
    float x;
    float y;
};

std::ostream& operator<<(std::ostream& ostream, const Vector& vector);
Vector operator+(const Vector& left, const Vector& right);
Vector operator-(const Vector& left, const Vector& right);

#endif /* Vector_hpp */
