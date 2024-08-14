#pragma once

// Header file includes
#include <cmath>

// Vector2 struct definition
struct vector2 {
    vector2(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    vector2(int* data) : x(data[0]), y(data[1]) {}
    long long x, y;
};

// Function prototypes

// Addition
vector2 operator +(vector2 x, vector2 y);

// Subtraction
vector2 operator -(vector2 x, vector2 y);

// Element-wise multiplication
vector2 operator *(vector2 x, vector2 y);

// Scalar multiplication
vector2 operator *(vector2, float);
vector2 operator *(float, vector2);

// Cross product
long long cross(vector2 x, vector2 y);

// Dot product
long long dot(vector2 x, vector2 y);

// Integer division with rounding
long long dv(long long a, long long b);

// Squared length of the vector
long long len(vector2 x);

// Magnitude (length) of the vector
long long dis(vector2 x);

// Division (projection of one vector onto another)
vector2 operator /(vector2 x, vector2 y);

// Modulus (remainder after projection)
vector2 operator %(vector2 x, vector2 y);

// Greatest Common Divisor (GCD) for vectors
vector2 gcd(vector2 x, vector2 y);

// Calculate a point on a Bezier curve
vector2 calcBezierPoint(float t, vector2 p0, vector2 p1, vector2 p2, vector2 p3);
