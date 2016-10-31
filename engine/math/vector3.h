#ifndef __BELLUM_VECTOR3_H__
#define __BELLUM_VECTOR3_H__

#include "math.h"
#include <ostream>

namespace bellum {

struct Vector3 {
  float x, y, z;

  inline void setMagnitude(float magnitude);
  inline void setSquaredMagnitude(float sqrMagnitude);

  inline float magnitude() const;
  inline float squaredMagnitude() const;
  inline Vector3& normalize();
  inline Vector3 normalized() const;

  inline Vector3 operator+(const Vector3& v) const;
  inline Vector3& operator+=(const Vector3& v);
  inline Vector3 operator-(const Vector3& v) const;
  inline Vector3& operator-=(const Vector3& v);
  inline Vector3 operator-() const;
  inline Vector3 operator*(float a) const;
  inline Vector3& operator*=(float a);
  inline Vector3 operator/(float a) const;
  inline Vector3& operator/=(float x);
  inline bool operator==(const Vector3& v) const;
  inline bool operator!=(const Vector3& v) const;

  inline static float angle(const Vector3& from, const Vector3& to);
  inline static Vector3 clampMagnitude(const Vector3& v, float max);
  inline static Vector3 cross(const Vector3& a, const Vector3& b);
  inline static float distance(const Vector3& a, const Vector3& b);
  inline static float squaredDistance(const Vector3& a, const Vector3& b);
  inline static float dot(const Vector3& a);
  inline static float dot(const Vector3& a, const Vector3& b);
  inline static Vector3 lerp(const Vector3& a, const Vector3& b, float t);
  inline static Vector3 lerpUnclamped(const Vector3& a, const Vector3& b, float t);
  inline static Vector3 max(const Vector3& a, const Vector3& b);
  inline static Vector3 min(const Vector3& a, const Vector3& b);
  inline static Vector3 moveTowards(const Vector3& current, const Vector3& target, float delta);
  inline static Vector3 project(const Vector3& v, const Vector3& on);
  inline static Vector3 projectOnPlane(const Vector3& v, const Vector3& planeNormal);
  inline static Vector3 reflect(const Vector3& in, const Vector3& normal);
  inline static Vector3 rotate(const Vector3& v, const Vector3& axis, float angle);
  inline static Vector3 slerp(const Vector3& a, const Vector3& b, float t);
  inline static Vector3 slerpUnclamped(const Vector3& a, const Vector3& b, float t);
  inline static Vector3 clamp(const Vector3& v, const Vector3& min, const Vector3& max);
  inline static Vector3 scale(const Vector3& a, const Vector3& b);

  inline static const Vector3& back();
  inline static const Vector3& down();
  inline static const Vector3& forward();
  inline static const Vector3& left();
  inline static const Vector3& right();
  inline static const Vector3& up();
  inline static const Vector3& zero();
  inline static const Vector3& one();

  inline friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};

inline void Vector3::setMagnitude(float magnitude) {
  this->setSquaredMagnitude(magnitude * magnitude);
}

inline void Vector3::setSquaredMagnitude(float sqrMagnitude) {
  float sm = this->squaredMagnitude();

  if (sm != 0.0f && sm != sqrMagnitude) {
    float s = Math::sqrt(sqrMagnitude / sm);
    x *= s;
    y *= s;
    z *= s;
  }
}

// Properties
inline float Vector3::magnitude() const {
  return Math::sqrt(x * x + y * y + z * z);
}

inline float Vector3::squaredMagnitude() const {
  return x * x + y * y + z * z;
}

inline Vector3& Vector3::normalize() {
  float m = magnitude();

  if (m != 0.0f) {
    x /= m;
    y /= m;
    z /= m;
  }

  return *this;
}

inline Vector3 Vector3::normalized() const {
  float m = magnitude();

  if (m != 0.0f) {
    return {x / m, y / m, z / m};
  }

  return *this;
}

// Operators
inline Vector3 Vector3::operator+(const Vector3& v) const {
  return {x + v.x, y + v.y, z + v.z};
}

inline Vector3& Vector3::operator+=(const Vector3& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

inline Vector3 Vector3::operator-(const Vector3& v) const {
  return {x - v.x, y - v.y, z - v.z};
}

inline Vector3& Vector3::operator-=(const Vector3& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

inline Vector3 Vector3::operator-() const {
  return {-x, -y, -z};
}

inline Vector3 Vector3::operator*(float a) const {
  return {x * a, y * a, z * a};
}

inline Vector3& Vector3::operator*=(float a) {
  x *= a;
  y *= a;
  z *= a;
  return *this;
}

inline Vector3 Vector3::operator/(const float a) const {
  return {x / a, y / a, z / a};
}

inline Vector3& Vector3::operator/=(const float a) {
  x /= a;
  y /= a;
  z /= a;
  return *this;
}

inline bool Vector3::operator==(const Vector3& v) const {
  return x == v.x && y == v.y && z == v.z;
}

inline bool Vector3::operator!=(const Vector3& v) const {
  return x != v.x || y != v.y || z != v.z;
}

inline Vector3 operator*(float a, const Vector3& v) {
  return {
    v.x * a,
    v.x * a,
    v.z * a,
  };
}

// Algebra
inline float Vector3::angle(const Vector3& from, const Vector3& to) {
  float dls = dot(from, to) / (from.magnitude() * to.magnitude());

  if (dls < -1.0f) {
    dls = -1.0f;
  } else if (dls > 1.0f) {
    dls = 1.0f;
  }

  return Math::acos(dls);
}

inline Vector3 Vector3::clampMagnitude(const Vector3& v, float max) {
  Vector3 result{v};

  if (v.magnitude() > max) {
    result.normalize();
    result *= max;
  }

  return result;
}

inline Vector3 Vector3::cross(const Vector3& a, const Vector3& b) {
  return {
    a.y * b.z - b.y * a.z,
    a.z * b.x - b.z * a.x,
    a.x * b.y - b.x * a.y
  };
}

inline float Vector3::distance(const Vector3& a, const Vector3& b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  float dz = b.z - a.z;
  return Math::sqrt(dx * dx + dy * dy + dz * dz);
}

inline float Vector3::squaredDistance(const Vector3& a, const Vector3& b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  float dz = b.z - a.z;
  return dx * dx + dy * dy + dz * dz;
}

inline float Vector3::dot(const Vector3& a) {
  return a.x * a.x + a.y * a.y + a.z * a.z;
}

inline float Vector3::dot(const Vector3& a, const Vector3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vector3 Vector3::lerp(const Vector3& a, const Vector3& b, float t) {
  return lerpUnclamped(a, b, Math::clamp(t, 0.0f, 1.0f));
}

inline Vector3 Vector3::lerpUnclamped(const Vector3& a, const Vector3& b, float t) {
  return {
    a.x + (b.x - a.x) * t,
    a.y + (b.y - a.y) * t,
    a.z + (b.z - a.z) * t
  };
}

inline Vector3 Vector3::max(const Vector3& a, const Vector3& b) {
  return {
    Math::max(a.x, b.x),
    Math::max(a.y, b.y),
    Math::max(a.z, b.z)
  };
}

inline Vector3 Vector3::min(const Vector3& a, const Vector3& b) {
  return {
    Math::min(a.x, b.x),
    Math::min(a.y, b.y),
    Math::min(a.z, b.z)
  };
}

Vector3 Vector3::moveTowards(const Vector3& current, const Vector3& target, float delta) {
  Vector3 d = (target - current).normalized();
  return current + d * delta;
}

inline Vector3 Vector3::project(const Vector3& v, const Vector3& on) {
  return on * (dot(on, v) / on.squaredMagnitude());
}

Vector3 Vector3::projectOnPlane(const Vector3& v, const Vector3& planeNormal) {
  return v - project(v, planeNormal);
}

inline Vector3 Vector3::reflect(const Vector3& in, const Vector3& normal) {
  return in - 2.0f * dot(in, normal) * normal;
}

inline Vector3 Vector3::rotate(const Vector3& v, const Vector3& axis, float angle) {
  float sin = Math::sin(-angle);
  float cos = Math::cos(-angle);

  return cross(v, axis * sin) + v * cos + axis * dot(axis * (1.0f - cos));
}

inline Vector3 Vector3::slerp(const Vector3& a, const Vector3& b, float t) {
  return slerpUnclamped(a, b, Math::clamp(t, 0.0f, 1.0f));
}

inline Vector3 Vector3::slerpUnclamped(const Vector3& a, const Vector3& b, float t) {
  float d = dot(a, b);

  if (d > 0.9995f || d < -0.9995f) {
    return lerp(a, b, t);
  }

  float theta0 = Math::acos(d);
  float theta = theta0 * t;

  float st = Math::sin(theta);
  float tx = b.x - a.x * d;
  float ty = b.y - a.y * d;
  float tz = b.z - a.z * d;
  float l2 = tx * tx + ty * ty + tz * tz;
  float dl = st * ((l2 < 0.0001f) ? 1.0f : 1.0f / Math::sqrt(l2));

  float cost = Math::cos(theta);

  return Vector3{a.x * cost + (tx * dl),
                 a.y * cost + (ty * dl),
                 a.z * cost + (tz * dl)}
    .normalized();
}

inline Vector3 Vector3::clamp(const Vector3& v, const Vector3& min, const Vector3& max) {
  return {
    Math::clamp(v.x, min.x, max.x),
    Math::clamp(v.y, min.y, max.y),
    Math::clamp(v.z, min.z, max.z)
  };
}

inline Vector3 Vector3::scale(const Vector3& a, const Vector3& b) {
  return {
    a.x * b.x,
    a.y * b.y,
    a.z * b.z
  };
}

// Singletons
const Vector3& Vector3::back() {
  static Vector3 v{0.0f, 0.0f, -1.0f};
  return v;
}

const Vector3& Vector3::down() {
  static Vector3 v{0.0f, -1.0f, 0.0f};
  return v;
}

const Vector3& Vector3::forward() {
  static Vector3 v{0.0f, 0.0f, 1.0f};
  return v;
}

const Vector3& Vector3::left() {
  static Vector3 v{-1.0f, 0.0f, 0.0f};
  return v;
}

const Vector3& Vector3::right() {
  static Vector3 v{1.0f, 0.0f, 0.0f};
  return v;
}

const Vector3& Vector3::up() {
  static Vector3 v{0.0f, 1.0f, 0.0f};
  return v;
}

const Vector3& Vector3::zero() {
  static Vector3 v{0.0f, 0.0f, 0.0f};
  return v;
}

const Vector3& Vector3::one() {
  static Vector3 v{1.0f, 1.0f, 1.0f};
  return v;
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
  os << "Vector3(x: " << v.x << ", y: " << v.y << ", z: " << v.z << ")";
  return os;
}

}

#endif
