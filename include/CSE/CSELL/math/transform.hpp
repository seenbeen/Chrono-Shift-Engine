#ifndef CSELL_MATH_TRANSFORM_HPP
#define CSELL_MATH_TRANSFORM_HPP

#include <CSE/CSELL/math/vector3f.hpp>

namespace CSELL { namespace Math {
    struct Transform {
        // order of operations = scale, orient, move
        Vector3f orientation;
        Vector3f scale;
        Vector3f position;
        Transform();
        ~Transform();
    };
}}
#endif // CSELL_MATH_TRANSFORM_HPP
