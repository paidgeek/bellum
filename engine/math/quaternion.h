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

  inline Quaternion();
  inline Quaternion(float x, float y, float z, float w);
  inline Quaternion(const float* data);
  Quaternion(const Vector3& axis, float angle);
  Quaternion(const Matrix4& m);

  inline Quaternion(const Quaternion& q);
  inline Quaternion& operator=(const Quaternion& q);

  inline void set(const Quaternion& q);
  inline void set(float x, float y, float z, float w);
  inline void set(const float* data);
  void set(const Vector3& axis, float angle);
  void set(const Matrix4& m);

  inline Quaternion operator*(const Quaternion& q) const;
  inline Quaternion& operator*=(const Quaternion& q);

  Vector3 toEulerAngles() const;
  inline float magnitude() const;
  inline float squaredMagnitude() const;
  inline void normalize(Quaternion& dst) const;
  inline Quaternion& normalize();
  inline void conjugate(Quaternion& dst) const;
  inline Quaternion& conjugate();
  inline void inverse(Quaternion& dst) const;
  inline Quaternion& inverse();

  inline static float dot(const Quaternion& q);
  inline static float dot(const Quaternion& a, const Quaternion& b);
  inline static void multiply(const Quaternion& a, const Quaternion& b, Quaternion& dst);
  static void rotatePoint(const Quaternion& q, const Vector3& point, Vector3& dst);
  inline static void lerp(const Quaternion& a, const Quaternion& b, float t, Quaternion& dst);
  inline static void slerp(const Quaternion& a, const Quaternion& b, float t, Quaternion& dst);

  static void makeIdentity(Quaternion& dst);
  static void makeEuler(const Vector3& eulerAngles, Quaternion& dst);
  static void makeEuler(float x, float y, float z, Quaternion& dst);
  static void makeAxisAngle(const Vector3& axis, float angle, Quaternion& dst);
  static void makeLookAt(const Vector3& direction, const Vector3& up, Quaternion& dst);

  inline static const Quaternion& identity();
  inline static const Quaternion& zero();

  friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
};

// Constructors
Quaternion::Quaternion() {}

Quaternion::Quaternion(float x, float y, float z, float w)
  : x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion(const float* data)
  : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}

Quaternion::Quaternion(const Quaternion& q) {
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
}

Quaternion& Quaternion::operator=(const Quaternion& q) {
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
}

// Setters
inline void Quaternion::set(const Quaternion& q) {
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
}

inline void Quaternion::set(float x, float y, float z, float w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

inline void Quaternion::set(const float* data) {
  x = data[0];
  y = data[1];
  z = data[2];
  w = data[3];
}

// Operators
inline Quaternion Quaternion::operator*(const Quaternion& q) const {
  Quaternion result;
  multiply(*this, q, result);
  return result;
}

inline Quaternion& Quaternion::operator*=(const Quaternion& q) {
  multiply(*this, q, *this);
  return *this;
}

// Algebra
inline float Quaternion::magnitude() const {
  return Math::sqrt(x * x + y * y + z * z + w * w);
}

inline float Quaternion::squaredMagnitude() const {
  return x * x + y * y + z * z + w * w;
}

inline void Quaternion::normalize(Quaternion& dst) const {
  float m = magnitude();

  if (m != 0.0f) {
    dst.set(x / m, y / m, z / m, w / m);
  } else {
    dst.set(0.0f, 0.0f, 0.0f, 1.0f);
  }
}

inline Quaternion& Quaternion::normalize() {
  float m = this->magnitude();

  if (m != 0.0f) {
    x /= m;
    y /= m;
    z /= m;
    w /= m;
  }

  return *this;
}

inline float Quaternion::dot(const Quaternion& q) {
  return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

inline float Quaternion::dot(const Quaternion& a, const Quaternion& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline void Quaternion::conjugate(Quaternion& dst) const {
  dst.set(-x, -y, -z, w);
}

inline Quaternion& Quaternion::conjugate() {
  this->x = -x;
  this->y = -y;
  this->w = -z;

  return *this;
}

void Quaternion::inverse(Quaternion& dst) const {
  dst.set(*this);
  dst.normalize();
  dst.conjugate();
}

inline Quaternion& Quaternion::inverse() {
  this->normalize();
  this->conjugate();
  return *this;
}

inline void Quaternion::multiply(const Quaternion& a, const Quaternion& b, Quaternion& dst) {
  dst.set(
    a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
    a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
    a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
    a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
  );
}

inline void Quaternion::lerp(const Quaternion& a, const Quaternion& b, float t, Quaternion& dst) {
  if (t == 0.0f) {
    dst.set(a);
    return;
  } else if (t == 1.0f) {
    dst.set(b);
    return;
  }

  float t1 = 1.0f - t;

  dst.set(
    t1 * a.x + t * b.x,
    t1 * a.y + t * b.y,
    t1 * a.z + t * b.z,
    t1 * a.w + t * b.w
  );
}

inline void Quaternion::slerp(const Quaternion& a, const Quaternion& b, float t, Quaternion& dst) {
  if (t == 0.0f) {
    dst.set(a);
    return;
  } else if (t == 1.0f) {
    dst.set(b);
    return;
  }

  if (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w) {
    dst.set(a);
    return;
  }

  float halfY, alpha, beta;
  float u, f1, f2a, f2b;
  float ratio1, ratio2;
  float halfSecHalfTheta, versHalfTheta;
  float sqNotU, sqU;

  float cosTheta = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;

  alpha = cosTheta >= 0 ? 1.0f : -1.0f;
  halfY = 1.0f + alpha * cosTheta;

  f2b = t - 0.5f;
  u = f2b >= 0 ? f2b : -f2b;
  f2a = u - f2b;
  f2b += u;
  u += u;
  f1 = 1.0f - u;

  halfSecHalfTheta = 1.09f - (0.476537f - 0.0903321f * halfY) * halfY;
  halfSecHalfTheta *= 1.5f - halfY * halfSecHalfTheta * halfSecHalfTheta;
  versHalfTheta = 1.0f - halfY * halfSecHalfTheta;

  sqNotU = f1 * f1;
  ratio2 = 0.0000440917108f * versHalfTheta;
  ratio1 = -0.00158730159f + (sqNotU - 16.0f) * ratio2;
  ratio1 = 0.0333333333f + ratio1 * (sqNotU - 9.0f) * versHalfTheta;
  ratio1 = -0.333333333f + ratio1 * (sqNotU - 4.0f) * versHalfTheta;
  ratio1 = 1.0f + ratio1 * (sqNotU - 1.0f) * versHalfTheta;

  sqU = u * u;
  ratio2 = -0.00158730159f + (sqU - 16.0f) * ratio2;
  ratio2 = 0.0333333333f + ratio2 * (sqU - 9.0f) * versHalfTheta;
  ratio2 = -0.333333333f + ratio2 * (sqU - 4.0f) * versHalfTheta;
  ratio2 = 1.0f + ratio2 * (sqU - 1.0f) * versHalfTheta;

  f1 *= ratio1 * halfSecHalfTheta;
  f2a *= ratio2;
  f2b *= ratio2;
  alpha *= f1 + f2a;
  beta = f1 + f2b;

  float w = alpha * a.w + beta * b.w;
  float x = alpha * a.x + beta * b.x;
  float y = alpha * a.y + beta * b.y;
  float z = alpha * a.z + beta * b.z;

  f1 = 1.5f - 0.5f * (w * w + x * x + y * y + z * z);
  dst.set(x * f1, y * f1, z * f1, w * f1);
}

// Singletons
const Quaternion& Quaternion::identity() {
  static Quaternion value{0.0f, 0.0f, 0.0f, 1.0f};
  return value;
}

const Quaternion& Quaternion::zero() {
  static Quaternion value{0.0f, 0.0f, 0.0f, 0.0f};
  return value;
}

inline std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
  os << "Quaternion(" << "x: " << q.x << ", y: " << q.y << ", z: " << q.z << ", w: " << q.w << ')';
  return os;
}

}

#endif
