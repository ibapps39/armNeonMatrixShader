#pragma once
#include <random>
class vec3
{
private:
public:
    float e[3];
    enum dim
    {
        X,
        Y,
        Z
    };
    vec3() : e{0, 0, 0} {}
    vec3(float x, float y, float z) : e{x, y, z} {}
    float x() const { return e[X]; }
    float y() const { return e[Y]; };
    float z() const { return e[Z]; };
    float operator[](int i) const { return e[i]; };
    float &operator[](int i) { return e[i]; };
    // Vec Addit.
    vec3 &operator+=(const vec3 &v)
    {
        e[X] += v.e[X];
        e[Y] += v.e[Y];
        e[Z] += v.e[Z];
        return *this;
    }
    // Vector Sub.
    vec3 &operator-=(const vec3 &v)
    {
        e[X] -= v.e[X];
        e[Y] -= v.e[Y];
        e[Z] -= v.e[Z];
        return *this;
    }
    // Scalar Multi.
    vec3 &operator*=(float S)
    {
        e[X] *= S;
        e[Y] *= S;
        e[Z] *= S;
        return *this;
    }
    // Scalar Div.
    vec3 &operator/=(float S)
    {
        return *this *= 1 / S;
    }
    // Vec len squared, float
    float len_sqf() const
    {
        return ((e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]));
    }
    float len_f() const
    {
        return sqrtf(vec3::len_sqf());
    }
    float len_fast() const
    {
        // FUTURE FAST APPROX
        int x = vec3::len_f();
        int i = *(int *)&x;
        i = (i >> 1) + 0x1FC00000; // initial guess
        return *(float *)&i;
    }
    inline void normalize()
    {
        float length = vec3::len_f();
        *this = (length == 0 || length < 1e-8) ? vec3(0,0,0) : vec3(this->x()/length, this->x()/length, this->x()/length);
    }
};
inline vec3 rand_vec()
{
    return vec3(
        rand() % 101,
        rand() % 101,
        rand() % 101);
}
inline vec3 rand_vecf()
{
    return vec3(
        rand() / (float)(RAND_MAX) * 101,
        rand() / (float)(RAND_MAX) * 101,
        rand() / (float)(RAND_MAX) * 101
    );
}

vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(
        u[vec3::X] + v[vec3::X],
        u[vec3::Y] + v[vec3::Y],
        u[vec3::Z] + v[vec3::Z]);
}
vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(
        u[vec3::X] - v[vec3::X],
        u[vec3::Y] - v[vec3::Y],
        u[vec3::Z] - v[vec3::Z]);
}
/// @brief Dot product shorthand
/// @param u &vec3
/// @param v &vec3
/// @return vec3
vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(
        u[vec3::X] * v[vec3::X],
        u[vec3::Y] * v[vec3::Y],
        u[vec3::Z] * v[vec3::Z]);
}
vec3 operator*(float t, const vec3 &v)
{
    return vec3(
        t * v[vec3::X],
        t * v[vec3::Y],
        t * v[vec3::Z]);
}
vec3 operator*(const vec3 &v, float t)
{
    return t * v;
}

vec3 operator/(const vec3 &v, float t)
{
    return (1.0f / t) * v;
}
vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(
        u.e[vec3::Y] * v.e[vec3::Z] - u.e[vec3::Z] * v.e[vec3::Y],
        u.e[vec3::Z] * v.e[vec3::X] - u.e[vec3::X] * v.e[vec3::Z],
        u.e[vec3::X] * v.e[vec3::Y] - u.e[vec3::Y] * v.e[vec3::X]
    );
}
inline void normalize(const vec3& u)
{
    float length = u.len_f();
    (length == 0 || length < 1e-8) ? vec3(0,0,0) : u/length;
}
std::ostream& operator<<(std::ostream& out, vec3& u)
{
    return out << u.e[vec3::X] << ", " << u.e[vec3::Y] << ", " << u.e[vec3::Z];
}