#pragma once

struct Vec3f {
    Vec3f(): x(0.0f), y(0.0f), z(0.0f) {};
    Vec3f(const Vec3f& v): x(v.x), y(v.y), z(v.z) {};
    Vec3f(float x, float y, float z): x(x), y(y), z(z) {};
    float x;
    float y;
    float z;
};

struct Vec4f {
    Vec4f(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
    Vec4f(const Vec4f& v): x(v.x), y(v.y), z(v.z), w(v.w) {};
    Vec4f(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {};
    Vec4f(const Vec3f& v): x(v.x), y(v.y), z(v.z), w(0.0) {};
    float x;
    float y;
    float z;
    float w;
};

bool point(Vec4f vec);

bool vector(Vec4f vec);

bool eq(Vec4f lhs, Vec4f rhs);

Vec4f add(Vec4f lhs, Vec4f rhs);

Vec4f sub(Vec4f lhs, Vec4f rhs);

Vec4f mul(float scale, Vec4f vec);
Vec4f mul(Vec4f vec, float scale );

Vec4f div(float scale, Vec4f vec);
Vec4f div(Vec4f vec, float scale );

float mag(Vec4f vec);

Vec4f norm(Vec4f vec);

float dot(Vec4f lhs, Vec4f rhs);

Vec4f cross(Vec4f lhs, Vec4f rhs);

Vec4f operator+(const Vec4f lhs, const Vec4f rhs); 
Vec4f operator-(const Vec4f lhs, const Vec4f rhs);
bool operator==(const Vec4f lhs, const Vec4f rhs);



