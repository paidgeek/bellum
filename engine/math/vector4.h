#ifndef BELLUM_VECTOR4_H
#define BELLUM_VECTOR4_H

#include "vector3.h"

namespace bellum {

struct Vector4 {
  float x, y, z, w;

  inline void setMagnitude(float magnitude);
  inline void setSquaredMagnitude(float sqrMagnitude);

  inline float magnitude() const;
  inline float squaredMagnitude() const;
  inline Vector4& normalize();
  inline Vector4 normalized() const;

  inline Vector4 operator+(const Vector4& v) const;
  inline Vector4& operator+=(const Vector4& v);
  inline Vector4 operator-(const Vector4& v) const;
  inline Vector4& operator-=(const Vector4& v);
  inline Vector4 operator-() const;
  inline Vector4 operator*(float a) const;
  inline Vector4& operator*=(float a);
  inline Vector4 operator/(float a) const;
  inline Vector4& operator/=(float x);
  inline bool operator==(const Vector4& v) const;
  inline bool operator!=(const Vector4& v) const;

  inline static float distance(const Vector4& a, const Vector4& b);
  inline static float squaredDistance(const Vector4& a, const Vector4& b);
  inline static float dot(const Vector4& a);
  inline static float dot(const Vector4& a, const Vector4& b);
  inline static Vector4 lerp(const Vector4& a, const Vector4& b, float t);
  inline static Vector4 lerpUnclamped(const Vector4& a, const Vector4& b, float t);
  inline static Vector4 max(const Vector4& a, const Vector4& b);
  inline static Vector4 min(const Vector4& a, const Vector4& b);
  inline static Vector4 moveTowards(const Vector4& current, const Vector4& target, float delta);
  inline static Vector4 project(const Vector4& v, const Vector4& on);
  inline static Vector4 scale(const Vector4& a, const Vector4& b);

  inline static const Vector4& zero();
  inline static const Vector4& one();

  inline friend std::ostream& operator<<(std::ostream& os, const Vector4& vector3);
};

inline void Vector4::setMagnitude(float magnitude) {
  this->setSquaredMagnitude(magnitude * magnitude);
}

inline void Vector4::setSquaredMagnitude(float sqrMagnitude) {
  float sm = this->squaredMagnitude();

  if (sm != 0.0f && sm != sqrMagnitude) {
    float s = Math::sqrt(sqrMagnitude / sm);
    x *= s;
    y *= s;
    z *= s;
    w *= s;
  }
}

// Properties
inline float Vector4::magnitude() const {
  return Math::sqrt(x * x + y * y + z * z + w * w);
}

inline float Vector4::squaredMagnitude() const {
  return x * x + y * y + z * z + w * w;
}

inline Vector4& Vector4::normalize() {
  float m = this->magnitude();

  if (m != 0.0f) {
    x /= m;
    y /= m;
    z /= m;
    w /= m;
  }

  return *this;
}

inline Vector4 Vector4::normalized() const {
  float m = this->magnitude();

  if (m != 0.0f) {
    return {x / m, y / m, z / m, w / m};
  }

  return *this;
}

// Operators
inline Vector4 Vector4::operator+(const Vector4& v) const {
  return {x + v.x, y + v.y, z + v.z, w + v.w};
}

inline Vector4& Vector4::operator+=(const Vector4& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;
  return *this;
}

inline Vector4 Vector4::operator-(const Vector4& v) const {
  return {x - v.x, y - v.y, z - v.z, w - v.w};
}

inline Vector4& Vector4::operator-=(const Vector4& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;
  return *this;
}

inline Vector4 Vector4::operator-() const {
  return {-x, -y, -z, -w};
}

inline Vector4 Vector4::operator*(float a) const {
  return {x * a, y * a, z * a, w * a};
}

inline Vector4& Vector4::operator*=(float a) {
  x *= a;
  y *= a;
  z *= a;
  w *= a;
  return *this;
}

inline Vector4 Vector4::operator/(const float a) const {
  return {x / a, y / a, z / a, w / a};
}

inline Vector4& Vector4::operator/=(const float a) {
  x /= a;
  y /= a;
  z /= a;
  w /= a;
  return *this;
}

inline bool Vector4::operator==(const Vector4& v) const {
  return x == v.x && y == v.y && z == v.z && w == v.w;
}

inline bool Vector4::operator!=(const Vector4& v) const {
  return x != v.x || y != v.y || z != v.z || w != v.w;
}

inline Vector4 operator*(float a, const Vector4& v) {
  return {
    v.x * a,
    v.x * a,
    v.z * a,
    v.w * a
  };
}

// Algebra
inline float Vector4::distance(const Vector4& a, const Vector4& b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  float dz = b.z - a.z;
  float dw = b.w - a.w;
  return Math::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

inline float Vector4::squaredDistance(const Vector4& a, const Vector4& b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  float dz = b.z - a.z;
  float dw = b.w - a.w;
  return dx * dx + dy * dy + dz * dz + dw * dw;
}

inline float Vector4::dot(const Vector4& a) {
  return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}

inline float Vector4::dot(const Vector4& a, const Vector4& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w + b.w;
}

inline Vector4 Vector4::lerp(const Vector4& a, const Vector4& b, float t) {
  return lerpUnclamped(a, b, Math::clamp(t, 0.0f, 1.0f));
}

inline Vector4 Vector4::lerpUnclamped(const Vector4& a, const Vector4& b, float t) {
  return {
    a.x + (b.x - a.x) * t,
    a.y + (b.y - a.y) * t,
    a.z + (b.z - a.z) * t,
    a.w + (b.w - a.w) * t
  };
}

inline Vector4 Vector4::max(const Vector4& a, const Vector4& b) {
  return {
    Math::max(a.x, b.x),
    Math::max(a.y, b.y),
    Math::max(a.z, b.z),
    Math::max(a.w, b.w)
  };
}

inline Vector4 Vector4::min(const Vector4& a, const Vector4& b) {
  return {
    Math::min(a.x, b.x),
    Math::min(a.y, b.y),
    Math::min(a.z, b.z),
    Math::min(a.w, b.w)
  };
}

Vector4 Vector4::moveTowards(const Vector4& current, const Vector4& target, float delta) {
  Vector4 d = (target - current).normalized();
  return current + d * delta;
}

inline Vector4 Vector4::project(const Vector4& v, const Vector4& on) {
  return on * (dot(on, v) / on.squaredMagnitude());
}

inline Vector4 Vector4::scale(const Vector4& a, const Vector4& b) {
  return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

// Singletons
const Vector4& Vector4::zero() {
  static Vector4 v{0.0f, 0.0f, 0.0f, 0.0f};
  return v;
}

const Vector4& Vector4::one() {
  static Vector4 v{1.0f, 1.0f, 1.0f, 1.0f};
  return v;
}

inline std::ostream& operator<<(std::ostream& os, const Vector4& v) {
  os << "Vector4(x: " << v.x << ", y: " << v.y << ", z: " << v.z << ", w: " << v.w << ')';
  return os;
}

}

#endif
