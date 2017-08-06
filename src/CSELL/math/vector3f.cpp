#include <CSE/CSELL/math/vector3f.hpp>

#include <string>
#include <sstream>

#include <math.h>

#include <CSE/CSU/logger.hpp>

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

    Vector3f &Vector3f::operator+=(const Vector3f &other) { // addition assignment operator
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vector3f &Vector3f::operator-=(const Vector3f &other) { // subtraction assignment operator
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vector3f &Vector3f::operator*=(float x) { // scale assignment operator
        this->x *= x;
        this->y *= x;
        this->z *= x;
        return *this;
    }

    Vector3f &Vector3f::operator*=(const Vector3f &other) { // non-uniform scale assignment
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        return *this;
    }

    Vector3f &Vector3f::operator/=(float x) { // inverse scale assignment operator
        if (x == 0.0f) {
            CSU::Logger::log(CSU::Logger::WARN,CSU::Logger::CSELL, "Math - Vecto3f", "Attempting to scale by 1/0!");
            return *this;
        }
        this->x /= x;
        this->y /= x;
        this->z /= x;
        return *this;
    }

    Vector3f Vector3f::operator+(const Vector3f &other) { // addition
        return Vector3f(*this) += other;
    }

    Vector3f Vector3f::operator-(const Vector3f &other) { // subtraction
        return Vector3f(*this) -= other;
    }

    Vector3f Vector3f::operator*(float x) { // scale
        return Vector3f(*this) *= x;
    }

    Vector3f Vector3f::operator*(const Vector3f &other) { // non-uniform scale
        return Vector3f(*this) *= other;
    }

    Vector3f Vector3f::operator/(float x) { // inverse scale
        return Vector3f(*this) /= x;
    }

    Vector3f Vector3f::operator-() { // negation operator
        return Vector3f(*this) *= -1.0f;
    }

    // special operators

    float Vector3f::dot(const Vector3f &other) {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    Vector3f Vector3f::cross(const Vector3f &other) {
        return Vector3f(this->y*other.z - this->z*other.y,
                        this->z*other.x - this->x*other.z,
                        this->x*other.y - this->y*other.x); // cross product mathemagics
    }

    float Vector3f::magnitudeSquared() {
        return (*this).dot(*this);
    }

    float Vector3f::magnitude() {
        return sqrt(this->magnitudeSquared());
    }

    Vector3f Vector3f::normalized() {
        return (*this) / this->magnitude();
    }

    void Vector3f::normalize() {
        if (this->x == 0.0f && this->y == 0.0f && this->z == 0.0f) {
            CSU::Logger::log(CSU::Logger::WARN, CSU::Logger::CSELL, "Math - Vector3f", "Attempting to normalize the zero vector!");
            return;
        }
        (*this) /= this->magnitude();
    }

    std::string Vector3f::toString() {
        std::ostringstream stream;
        stream << "(" << this->x << ", " << this->y << ", " << this->z << ")";
        return stream.str();
    }
}}

