#ifndef CORE_MATH_VEC2_H_
#define CORE_MATH_VEC2_H_

#include <stdint.h>
#include <math.h>
#include <assert.h>

namespace rm
{
///
/// @brief
///     ℝ² vector
///     
struct vec2
{
    union
    {
        struct
        {
            float x;
            float y;
        };

        float coords[2];
    };


    /// (0,0)
    static const vec2 ZERO;
    /// (-1,0)
    static const vec2 LEFT;
    /// (1,0)
    static const vec2 RIGHT;
    /// (0,1)
    static const vec2 UP;
    /// (0,-1)
    static const vec2 DOWN;
    /// (1,1)
    static const vec2 ONE;



    vec2() : x{ 0 }, y{ 0 } {}
    
    vec2(float _x, float _y)
        : x{ _x }, y{ _y } {}
    

    vec2(const vec2& other)
        : x{other.x}, y{other.y} {}

    vec2& operator=(const vec2& other)
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    /// compare
    bool operator==(const vec2& other) const;
    /// not equal
    bool operator!=(const vec2& other) const;

    /// add another vector
    vec2 operator+(const vec2& other) const;
    
    /// negate
    vec2 operator-();
    /// subtract a vector
    vec2 operator-(const vec2& other) const;
    /// multiply by scalar
    vec2 operator*(float k) const;
    /// multiply by vector
    vec2 operator*(const vec2& other) const;

    /// divide by scalar
    vec2 operator/(float k) const;
    
    /// divide by a vector
    vec2 operator/(const vec2& other) const;
    
    /// add other vector to this
    vec2& operator+=(const vec2& other);

    /// substract other vector from this
    vec2& operator-=(const vec2& other);

    /// multiply this by k
    vec2& operator*=(float k);

    /// multiply this by other
    vec2& operator*=(const vec2& other);
    
    /// divide this by k
    vec2& operator/=(float k);
    
    /// divide this by other
    vec2& operator/=(const vec2& other);

    float length() const;

    float length_squared() const;
    
    vec2 normalized() const;

};

} // rm

#endif // CORE_MATH_VEC2_H_