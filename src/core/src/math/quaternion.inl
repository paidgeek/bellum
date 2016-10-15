#include "quaternion.h"

namespace bellum {

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

inline void Quaternion::setIdentity() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
  w = 1.0f;
}

inline void Quaternion::setEulerAngles(const Vector3& eulerAngles) {
  fromEuler(eulerAngles, this);
}

inline void Quaternion::setEulerAngles(float x, float y, float z) {
  fromEuler(x, y, z, this);
}

inline void Quaternion::setLookAt(const Vector3& direction, const Vector3& up) {
  fromLookAt(direction, up, this);
}

inline float& Quaternion::operator[](int i) {
  return (&this->x)[i];
}

// Operators
inline Quaternion Quaternion::operator*(const Quaternion& q) const {
  Quaternion result{*this};
  result.multiply(q);
  return result;
}

inline Quaternion& Quaternion::operator*=(const Quaternion& q) {
  this->multiply(q);
  return *this;
}

// Algebra
inline float Quaternion::magnitude() const {
  return Math::sqrt(x * x + y * y + z * z + w * w);
}

inline float Quaternion::squaredMagnitude() const {
  return x * x + y * y + z * z + w * w;
}

inline void Quaternion::normalize(Quaternion* dst) const {
  float m = this->magnitude();

  if (m != 0.0f) {
    dst->x /= m;
    dst->y /= m;
    dst->z /= m;
    dst->w /= m;
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

inline float Quaternion::dot(const Quaternion& q) const {
  return x * q.x + y * q.y + z * q.z + w * q.w;
}

inline float Quaternion::dot(const Quaternion& a, const Quaternion& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline void Quaternion::conjugate(Quaternion* dst) const {
  dst->set(-x, -y, -z, w);
}

inline Quaternion& Quaternion::conjugate() {
  this->x = -x;
  this->y = -y;
  this->w = -z;

  return *this;
}

void Quaternion::inverse(Quaternion* dst) const {
  dst->set(*this);
  dst->normalize();
  dst->conjugate();
}

inline Quaternion& Quaternion::inverse() {
  this->normalize();
  this->conjugate();
  return *this;
}

inline Quaternion& Quaternion::multiply(const Quaternion& q) {
  this->set(
    w * q.x + x * q.w + y * q.z - z * q.y,
    w * q.y - x * q.z + y * q.w + z * q.x,
    w * q.z + x * q.y - y * q.x + z * q.w,
    w * q.w - x * q.x - y * q.y - z * q.z
  );
}

inline void Quaternion::multiply(const Quaternion& a, const Quaternion& b, Quaternion* dst) {
  dst->set(
    a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
    a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
    a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
    a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
  );
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

}
