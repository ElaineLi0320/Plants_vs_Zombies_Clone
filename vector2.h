#pragma once

// Include necessary libraries
#include <cmath>

// Definition of the vector2 structure
struct vector2 {
    vector2(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    vector2(int* data) : x(data[0]), y(data[1]) {}
    long long x, y;
};

// Vector addition
vector2 operator +(vector2 x, vector2 y);

// Vector subtraction
vector2 operator -(vector2 x, vector2 y);

// Vector multiplication
vector2 operator *(vector2 x, vector2 y);
vector2 operator *(vector2 v, float scalar);
vector2 operator *(float scalar, vector2 v);

// Cross product
long long cross(vector2 x, vector2 y);

// Dot product
long long dot(vector2 x, vector2 y);

// Integer division
long long dv(long long a, long long b);

// Length squared of a vector
long long len(vector2 x);

// Magnitude of a vector
long long dis(vector2 x);

// Vector division
vector2 operator /(vector2 x, vector2 y);

// Vector modulus
vector2 operator %(vector2 x, vector2 y);

// Vector GCD (Greatest Common Divisor)
vector2 gcd(vector2 x, vector2 y);

// Bezier curve point calculation
vector2 calcBezierPoint(float t, vector2 p0, vector2 p1, vector2 p2, vector2 p3);
