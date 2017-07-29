#ifndef CSELL_MATH_VECTOR3F_HPP
#define CSELL_MATH_VECTOR3F_HPP

namespace CSELL { namespace Math {
    class Vector3f {
    public:
        float x, y, z;

        Vector3f();
        Vector3f(float x, float y, float z);
        Vector3f operator+(const Vector3f &other);
    };
}}
#endif
