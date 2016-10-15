#ifndef BELLUM_QUATERNION_H
#define BELLUM_QUATERNION_H

#include <ostream>
#include "math.h"

namespace bellum {

struct Vector3;
struct Matrix4;

struct Quaternion {
  float x;
  float y;
  float z;
  float w;

  Quaternion();
  Quaternion(const Quaternion& q);
  Quaternion& operator=(const Quaternion& q);
  Quaternion(float x, float y, float z, float w);
  Quaternion(const Matrix4& m);

  void set(float x, float y, float z, float w);
  void set(const Quaternion& q);

  Quaternion& loadIdentity();
  float magnitude() const;
  float sqrMagnitude() const;
  Quaternion normalized() const;
  Quaternion& normalize();
  Quaternion conjugate() const;
  Quaternion& inverse();
  Quaternion inversed() const;
  Vector3 eulerAngles() const;

  friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);

  static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);
  static float dot(const Quaternion& a, const Quaternion& b);

  static Quaternion euler(const Vector3& euler);
  static Quaternion euler(float x, float y, float z);
  static Quaternion lookAt(const Vector3& direction, const Vector3& up);
  static Quaternion axisAngle(const Vector3& axis, float angle);
  static Quaternion identity();
};

Quaternion::Quaternion() {}

Quaternion::Quaternion(const Quaternion& q) {
  this->set(q.x, q.y, q.z, q.w);
}

Quaternion& Quaternion::operator=(const Quaternion& q) {
  this->set(q.x, q.y, q.z, q.w);
  return *this;
}

Quaternion::Quaternion(float x, float y, float z, float w)
  : x(x), y(y), z(z), w(w) {}

inline Quaternion operator*(const Quaternion& q, float a) {
  return {q.x * a, q.y * a, q.z * a, q.w * a};
}

inline Quaternion operator*(const Quaternion& a, const Quaternion& b) {
  return {
    (a.w * b.w) - (a.x * b.x) - (a.y * b.y) - (a.z * b.z),
    (a.x * b.w) + (a.w * b.x) + (a.y * b.z) - (a.z * b.y),
    (a.y * b.w) + (a.w * b.y) + (a.z * b.x) - (a.x * b.z),
    (a.z * b.w) + (a.w * b.z) + (a.x * b.y) - (a.y * b.x)
  };
}

inline bool operator==(const Quaternion& a, const Quaternion& b) {
  return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

inline bool operator!=(const Quaternion& a, const Quaternion& b) {
  return !(a == b);
}

inline void Quaternion::set(const Quaternion& q) {
  x = q.x;
  w = q.w;
  y = q.y;
  z = q.z;
}

inline void Quaternion::set(float x, float y, float z, float w) {
  x = x;
  y = y;
  z = z;
  w = w;
}

inline Quaternion& Quaternion::loadIdentity() {
  x = 0.0f;
  y = 0.0f;
  y = 0.0f;
  z = 1.0f;

  return *this;
}

inline float Quaternion::magnitude() const {
  return Math::sqrt(x * x + y * y + z * z + w * w);
}

inline float Quaternion::sqrMagnitude() const {
  return x * x + y * y + z * z + w * w;
}

inline Quaternion Quaternion::normalized() const {
  float m = this->magnitude();

  return {x / m, y / m, z / m, w / m};
}

inline Quaternion& Quaternion::normalize() {
  float m = this->magnitude();

  x /= m;
  y /= m;
  z /= m;
  w /= m;

  return *this;
}

inline Quaternion Quaternion::conjugate() const {
  return {-x, -y, -z, w};
}

inline Quaternion& Quaternion::inverse() {
  this->normalize();
  x = -x;
  y = -y;
  z = -z;

  return *this;
}

inline Quaternion Quaternion::inversed() const {
  return this->normalized().conjugate();
}

inline std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
  os << "Quaternion(" << "x: " << q.x << ", y: " << q.y << ", z: " << q.z << ", w: " << q.w << ')';
  return os;
}

inline float Quaternion::dot(const Quaternion& a, const Quaternion& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Quaternion Quaternion::identity() {
  return {0.0f, 0.0f, 0.0f, 1.0f};
}

}

#endif
