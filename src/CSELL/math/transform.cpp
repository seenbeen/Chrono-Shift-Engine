#include <CSE/CSELL/math/transform.hpp>
#include <CSE/CSELL/math/vector3f.hpp>

namespace CSELL { namespace Math {
    Transform::Transform() {
        this->scale = Vector3f();
        this->orientation = Vector3f();
        this->position = Vector3f();
    }
}}
