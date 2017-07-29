#include <CSE/CSELL/math/vector3f.hpp>

namespace CSELL { namespace Math {
    Vector3f::Vector3f() {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    }

    Vector3f::Vector3f(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3f Vector3f::operator+(const Vector3f &other) {
        return Vector3f(this->x + other.x, this->y + other.y, this->z + other.z);
    }
}}

