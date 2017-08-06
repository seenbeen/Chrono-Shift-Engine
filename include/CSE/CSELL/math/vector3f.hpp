#ifndef CSELL_MATH_VECTOR3F_HPP
#define CSELL_MATH_VECTOR3F_HPP
#include <string>

namespace CSELL { namespace Math {
    class Vector3f {
    public:
        float x, y, z;

        Vector3f();
        Vector3f(float x, float y, float z);

        // assignment operators
        Vector3f &operator+=(const Vector3f &other);
        Vector3f &operator-=(const Vector3f &other);
        Vector3f &operator*=(float x);
        Vector3f &operator*=(const Vector3f &other);
        Vector3f &operator/=(float x);

        // binary operators
        Vector3f operator+(const Vector3f &other);
        Vector3f operator-(const Vector3f &other);
        Vector3f operator*(float x);
        Vector3f operator*(const Vector3f &other);
        Vector3f operator/(float x);

        // unary operators
        Vector3f operator-();

        // special operators
        float magnitudeSquared();
        float magnitude();
        float dot(const Vector3f &other);
        Vector3f cross(const Vector3f &other);

        Vector3f normalized(); // returns a copy
        void normalize(); // modifies this vector in place
        std::string toString();
    };
}}
#endif
