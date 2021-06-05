#pragma once
#include <string>

struct Vec3f {
    Vec3f() : x(0.0f), y(0.0f), z(0.0f){};
    Vec3f(const Vec3f& v) : x(v.x), y(v.y), z(v.z){};
    Vec3f(float x, float y, float z) : x(x), y(y), z(z){};
    float x;
    float y;
    float z;
};

struct Vec4f {
    Vec4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){};
    Vec4f(const Vec4f& v) : x(v.x), y(v.y), z(v.z), w(v.w){};
    Vec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){};
    Vec4f(const Vec3f& v) : x(v.x), y(v.y), z(v.z), w(0.0){};
    float x;
    float y;
    float z;
    float w;
};

bool point(const Vec4f& vec);

bool vector(const Vec4f& vec);

bool eq(const Vec4f& lhs, const Vec4f& rhs);
bool ne(const Vec4f& lhs, const Vec4f& rhs);

Vec4f add(const Vec4f& lhs, const Vec4f& rhs);

Vec4f sub(const Vec4f& lhs, const Vec4f& rhs);

Vec4f mul(float scale, const Vec4f& vec);
Vec4f mul(const Vec4f& vec, float scale);

Vec4f div(float scale, const Vec4f& vec);
Vec4f div(const Vec4f& vec, float scale);

float mag(const Vec4f& vec);

Vec4f norm(const Vec4f& vec);

float dot(const Vec4f& lhs, const Vec4f& rhs);

Vec4f cross(const Vec4f& lhs, const Vec4f& rhs);

Vec4f operator+(const Vec4f& lhs, const Vec4f& rhs);
Vec4f operator-(const Vec4f& lhs, const Vec4f& rhs);
bool operator==(const Vec4f& lhs, const Vec4f& rhs);

std::string str(const Vec4f& vec, unsigned int precision = 1);
