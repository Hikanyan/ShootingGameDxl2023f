#pragma once

#include <cmath>

namespace hikanyan {

struct Vector2 {
    float x{0.0f};
    float y{0.0f};

    constexpr Vector2() = default;
    constexpr Vector2(float x_value, float y_value) : x(x_value), y(y_value) {}

    [[nodiscard]] constexpr Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; }
    [[nodiscard]] constexpr Vector2 operator-(const Vector2& other) const { return {x - other.x, y - other.y}; }
    [[nodiscard]] constexpr Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
    [[nodiscard]] constexpr Vector2 operator/(float scalar) const { return {x / scalar, y / scalar}; }

    constexpr Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
    constexpr Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
    constexpr Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    constexpr Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    [[nodiscard]] float magnitude() const { return std::sqrt(x * x + y * y); }
};

struct Vector3 {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};

    constexpr Vector3() = default;
    constexpr Vector3(float x_value, float y_value, float z_value) : x(x_value), y(y_value), z(z_value) {}

    [[nodiscard]] constexpr Vector3 operator+(const Vector3& other) const { return {x + other.x, y + other.y, z + other.z}; }
    [[nodiscard]] constexpr Vector3 operator-(const Vector3& other) const { return {x - other.x, y - other.y, z - other.z}; }
    [[nodiscard]] constexpr Vector3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
    [[nodiscard]] constexpr Vector3 operator/(float scalar) const { return {x / scalar, y / scalar, z / scalar}; }

    constexpr Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    constexpr Vector3& operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    constexpr Vector3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    constexpr Vector3& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    [[nodiscard]] float magnitude() const { return std::sqrt(x * x + y * y + z * z); }
};

} // namespace hikanyan
