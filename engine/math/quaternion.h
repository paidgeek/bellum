#ifndef BELLUM_QUATERNION_H
#define BELLUM_QUATERNION_H

#include <ostream>
#include "../common.h"
#include "math.h"
#include "vector3.h"

namespace bellum {

struct Vector3;
struct Matrix4;

struct Quaternion {
  float x;
  float y;
  float z;
  float w;

  inline Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
  inline Quaternion(const float* data);
  inline Quaternion(const Quaternion& q);
  Quaternion(const Matrix4& m);
  inline Quaternion& operator=(const Quaternion& q);

  inline void set(float x, float y, float z, float w);
  inline void set(const float* data);
  void set(const Matrix4& m);
  inline float& operator[](int32 i);
  inline const float& operator[](int32 i) const;

  inline Quaternion operator*(const Quaternion& q) const;
  inline Quaternion& operator*=(const Quaternion& q);

  inline Vector3 eulerAngles() const;
  inline float magnitude() const;
  inline float squaredMagnitude() const;
  inline Quaternion& normalize();
  inline Quaternion normalized() const;
  inline Quaternion& conjugate();
  inline Quaternion conjugated() const;
  inline Quaternion& inverse();
  inline Quaternion inversed() const;

  inline static float angle(const Quaternion& a, const Quaternion& b);
  inline static Quaternion makeAngleAxis(float angle, const Vector3& axis);
  inline static float dot(const Quaternion& q);
  inline static float dot(const Quaternion& a, const Quaternion& b);
  inline static Quaternion makeEuler(const Vector3& euler);
  inline static Quaternion makeEuler(float x, float y, float z);
  inline static Quaternion makeFromToRotation(const Vector3& from, const Vector3& to);
  inline static Quaternion lerp(const Quaternion& a, const Quaternion& b, float t);
  inline static Quaternion lerpUnclamped(const Quaternion& a, const Quaternion& b, float t);
  inline static Quaternion makeLookRotation(const Vector3& forward, const Vector3& upwards);
  inline static Quaternion rotateTowards(const Quaternion& from, const Quaternion& to, float delta);
  inline static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);
  inline static Quaternion slerpUnclamped(const Quaternion& a, const Quaternion& b, float t);

  inline static const Quaternion& identity();

  friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
};

// Constructors
inline Quaternion::Quaternion(float x, float y, float z, float w)
  : x(x), y(y), z(z), w(w) {}

inline Quaternion::Quaternion(const float* data)
  : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}

inline Quaternion::Quaternion(const Quaternion& q) {
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
}

inline Quaternion& Quaternion::operator=(const Quaternion& q) {
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
}

// Setters
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

inline float& Quaternion::operator[](int32 i) {
  return *(&this->x + i);
}

inline const float& Quaternion::operator[](int32 i) const {
  return *(&this->x + i);
}

// Operators
inline Quaternion Quaternion::operator*(const Quaternion& q) const {
  return {
    w * q.x + x * q.w + y * q.z - z * q.y,
    w * q.y - x * q.z + y * q.w + z * q.x,
    w * q.z + x * q.y - y * q.x + z * q.w,
    w * q.w - x * q.x - y * q.y - z * q.z
  };
}

inline Quaternion& Quaternion::operator*=(const Quaternion& q) {
  set(
    w * q.x + x * q.w + y * q.z - z * q.y,
    w * q.y - x * q.z + y * q.w + z * q.x,
    w * q.z + x * q.y - y * q.x + z * q.w,
    w * q.w - x * q.x - y * q.y - z * q.z
  );
  return *this;
}

inline Vector3 operator*(const Quaternion& q, const Vector3& v) {
  // TODO
  return {};
}

// Properties
inline Vector3 Quaternion::eulerAngles() const {
  return {
    Math::atan2(2.0f * (w * x + y * z), 1.0f - 2.0f * (x * x + y * y)),
    Math::asin(2.0f * (w * y - z * x)),
    Math::atan2(2.0f * (w * z + x * y), 1.0f - 2.0f * (y * y + z * z))
  };
}

inline float Quaternion::magnitude() const {
  return Math::sqrt(x * x + y * y + z * z + w * w);
}

inline float Quaternion::squaredMagnitude() const {
  return x * x + y * y + z * z + w * w;
}

inline Quaternion& Quaternion::normalize() {
  float m = magnitude();

  if (m != 0.0f) {
    set(x / m, y / m, z / m, w / m);
  } else {
    set(0.0f, 0.0f, 0.0f, 1.0f);
  }

  return *this;
}

inline Quaternion Quaternion::normalized() const {
  float m = magnitude();

  if (m != 0.0f) {
    return {x / m, y / m, z / m, w / m};
  } else {
    return {0.0f, 0.0f, 0.0f, 1.0f};
  }

  return *this;
}

inline Quaternion& Quaternion::conjugate() {
  set(-x, -y, -z, w);
  return *this;
}

inline Quaternion Quaternion::conjugated() const {
  return {-x, -y, -z, w};
}

inline Quaternion& Quaternion::inverse() {
  normalize();
  conjugate();
  return *this;
}

inline Quaternion Quaternion::inversed() const {
  return normalized().conjugate();
}

// Algebra
float Quaternion::angle(const Quaternion& a, const Quaternion& b) {
  // TODO
}

Quaternion Quaternion::makeAngleAxis(float angle, const Vector3& axis) {
  float ha = angle / 2.0f;
  float sin = Math::sin(ha);
  Vector3 n = axis.normalized();

  return {n.x * sin, n.y * sin, n.z * sin, ha};
}

inline float Quaternion::dot(const Quaternion& q) {
  return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

inline float Quaternion::dot(const Quaternion& a, const Quaternion& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Quaternion Quaternion::makeEuler(const Vector3& euler) {
  return makeEuler(euler.x, euler.y, euler.z);
}

inline Quaternion Quaternion::makeEuler(float x, float y, float z) {
  x *= Math::kDegToRad ;
  y *= Math::kDegToRad ;
  z *= Math::kDegToRad ;

  float angle = x * 0.5;
   float sr = sin(angle);
   float cr = cos(angle);

  angle = y * 0.5;
   float sp = sin(angle);
   float cp = cos(angle);

  angle = z * 0.5;
   float sy = sin(angle);
   float cy = cos(angle);

   float cpcy = cp * cy;
   float spcy = sp * cy;
   float cpsy = cp * sy;
   float spsy = sp * sy;

  return {
    (sr * cpcy - cr * spsy),
    (cr * spcy + sr * cpsy),
    (cr * cpsy - sr * spcy),
    (cr * cpcy + sr * spsy)
  };
  /*
  float sinx = Math::sin(x);
  float cosx = Math::cos(x);
  float siny = Math::sin(y);
  float cosy = Math::cos(y);
  float sinz = Math::sin(z);
  float cosz = Math::cos(z);

  return {
    siny * cosx * cosz - cosy * sinx * sinz,
    cosy * sinx * cosz + siny * cosx * sinz,
    cosy * cosx * sinz - siny * sinx * cosz,
    cosy * cosx * cosz + siny * sinx * sinz
  };
  */
}

inline Quaternion Quaternion::makeFromToRotation(const Vector3& from, const Vector3& to) {
  // TODO
}

inline Quaternion Quaternion::lerp(const Quaternion& a, const Quaternion& b, float t) {
  return lerpUnclamped(a, b, Math::clamp(t, 0.0f, 1.0f));
}

inline Quaternion Quaternion::lerpUnclamped(const Quaternion& a, const Quaternion& b, float t) {
  if (t == 0.0f) {
    return a;
  } else if (t == 1.0f) {
    return b;
  }

  float t1 = 1.0f - t;

  return {
    t1 * a.x + t * b.x,
    t1 * a.y + t * b.y,
    t1 * a.z + t * b.z,
    t1 * a.w + t * b.w
  };
}

Quaternion Quaternion::rotateTowards(const Quaternion& from, const Quaternion& to, float delta) {
  // TODO
}

inline Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, float t) {
  return slerpUnclamped(a, b, Math::clamp(t, 0.0f, 1.0f));
}

Quaternion Quaternion::slerpUnclamped(const Quaternion& a, const Quaternion& b, float t) {
  if (t == 0.0f) {
    return a;
  } else if (t == 1.0f) {
    return b;
  }

  if (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w) {
    return a;
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
  return {x * f1, y * f1, z * f1, w * f1};
}

// Singletons
const Quaternion& Quaternion::identity() {
  static Quaternion value{0.0f, 0.0f, 0.0f, 1.0f};
  return value;
}

inline std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
  os << "Quaternion(" << "x: " << q.x << ", y: " << q.y << ", z: " << q.z << ", w: " << q.w << ')';
  return os;
}

}

#endif
