#include "Vector.hpp"

Vector operator+(const Vector& left, const Vector& right)
{
    return { left.x + right.x, left.y + right.y };
}

Vector operator-(const Vector& left, const Vector& right)
{
    return { left.x - right.x, left.y - right.y };
}

std::ostream& operator<<(std::ostream& ostream, const Vector& vector)
{
    return ostream << "(" << vector.x << "," << vector.y << ")";
}

float Vector::LengthVector() const
{
    return std::sqrt(x * x + y * y);
}

float Vector::LengthQuad() const
{
    return x * x + y * y;
}

float Vector::Scalar(const Vector& v) const
{
    return x * v.x + y * v.y;
}

Vector& Vector::Normalize()
{
    float length = LengthVector();
    x /= length;
    y /= length;
    
    return *this;
}

Vector& Vector::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    
    return *this;
}

Vector& Vector::operator+=(const Vector& v)
{
    x += v.x;
    y += v.y;
    
    return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
    x -= v.x;
    y -= v.y;
    
    return *this;
}

Vector Vector::operator-() const
{
    return Vector{ -x, -y };
}

bool Vector::operator==(const Vector& v) const
{
    return (x == v.x && y == v.y);
}

Vector& Vector::operator=(const Vector& v)
{
    x = v.x;
    y = v.y;
    return *this;
}
