#include <iostream>
#include <stdexcept>
class Vector3D;
inline Vector3D operator/(Vector3D v, float s);
class Vector3D {
public:
    Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z) {}
    Vector3D& operator= (const Vector3D& other) {
        if (&other == this) return *this;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    Vector3D(Vector3D&& other) : x(other.x), y(other.y), z(other.z) {}
    Vector3D& operator= (Vector3D&& other) {
        if (&other == this) return *this;
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    ~Vector3D() = default;

    Vector3D& operator+=(const Vector3D& other) noexcept {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vector3D& operator-=(const Vector3D& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vector3D& operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    Vector3D& operator/=(float s) {
        if (s == 0.0f) {
            throw std::runtime_error("Exception: Cannot divide by zero!");
            return *this;
        }
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    Vector3D operator-() const noexcept { return Vector3D(-x, -y, -z); }

    bool operator==(const Vector3D& rhs) const noexcept {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    bool operator!=(const Vector3D& rhs) const noexcept { return !(*this == rhs); }

    float length_squared() const noexcept { return x * x + y * y + z * z; }
    float length() const { return std::sqrt(length_squared()); }
    Vector3D normalized() const {
        float len = length();
        if (len == 0.0f) throw std::runtime_error("normalize zero vector");
        return *this / len;
    }

    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
};

inline Vector3D operator+(Vector3D lhs, const Vector3D& rhs) noexcept { return lhs += rhs; }
inline Vector3D operator-(Vector3D lhs, const Vector3D& rhs) noexcept { return lhs -= rhs; }
inline Vector3D operator*(Vector3D v, float s) noexcept { return v *= s; }
inline Vector3D operator*(float s, Vector3D v) noexcept { return v *= s; }
inline Vector3D operator/(Vector3D v, float s) { return v /= s; }
inline Vector3D operator/(const Vector3D& v, float s) {
    if (s == 0.0f) throw std::runtime_error("divide by zero");
    return Vector3D(v.x / s, v.y / s, v.z / s);
}

inline constexpr float dot(const Vector3D& a, const Vector3D& b) noexcept {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline constexpr Vector3D cross(const Vector3D& a, const Vector3D& b) noexcept{
    return Vector3D(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}
inline constexpr float length(const Vector3D& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    return os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}
