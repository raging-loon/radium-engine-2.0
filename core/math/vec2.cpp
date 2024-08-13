#include "vec2.h"

using rm::vec2;


const vec2 vec2::ZERO   { 0, 0};
const vec2 vec2::LEFT   {-1, 0};
const vec2 vec2::RIGHT  { 1, 0};
const vec2 vec2::UP     { 0, 1};
const vec2 vec2::DOWN   { 0,-1};
const vec2 vec2::ONE    { 1, 1};


bool vec2::operator==(const vec2& other) const
{
    return (other.x == x && other.y == y);
}

bool vec2::operator!=(const vec2& other) const
{
    return (other.x != x || other.y != y);
}

vec2 vec2::operator+(const vec2& other) const
{
    return vec2(other.x + x, other.y + y);
}

vec2 vec2::operator-()
{
    return vec2(-x, -y);
}

vec2 vec2::operator-(const vec2& other) const
{
    return vec2(x - other.x, y - other.y);
}

vec2 vec2::operator*(float k) const
{
    return vec2(x * k, y * k);
}

vec2 vec2::operator*(const vec2& other) const
{
    return vec2(x * other.x, y * other.y);
}

vec2 vec2::operator/(float k) const
{
    assert(k != 0);
    return vec2(x / k, y / k);
}

vec2 vec2::operator/(const vec2& other) const
{
    assert(other.x != 0 && other.y != 0);

    return vec2(x / other.x, y / other.y);
}

vec2& vec2::operator+=(const vec2& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

vec2& vec2::operator-=(const vec2& other)
{
    x -= other.x;
    y -= other.y;
    
    return *this;
}

vec2& vec2::operator*=(float k)
{
    x *= k;
    y *= k;
    return *this;
}

vec2& vec2::operator*=(const vec2& other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

vec2& vec2::operator/=(float k)
{
    assert(k != 0.0f);
    float invk = 1.0f / k;

    x /= invk;
    y /= invk;

    return *this;

}

vec2& vec2::operator/=(const vec2& other)
{
    assert(other.x != 0.0f && other.y != 0.0f);

    x /= other.x;
    y /= other.y;

    return *this;

}

float vec2::length() const
{
    return sqrtf(x * x + y * y);
}

float vec2::length_squared() const
{
    return x * x + y * y;
}

vec2 vec2::normalized() const
{
    float lensq = x * x + y * y;
    if (lensq != 1.0f && lensq > 0.0f)
    {
        float invlen = 1.0f / sqrtf(lensq);
        return *this * invlen;
    }

    return *this;
}