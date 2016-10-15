#include "vector3.h"

namespace bellum {

// Constructors
Vector3::Vector3() {}

Vector3::Vector3(const Vector3& v)
  : x(v.x), y(v.y), z(v.z) {}

Vector3& Vector3::operator=(const Vector3& v) {
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  return *this;
}

Vector3::Vector3(float x, float y, float z)
  : x(x), y(y), z(z) {}

Vector3::Vector3(float x, float y)
  : x(x), y(y), z(0.0f) {}

Vector3::Vector3(float a)
:x(a), y(a), z(a) {}

Vector3::Vector3(const float* data)
  : x(data[0]), y(data[1]), z(data[2]) {}

Vector3::Vector3(const Vector3& from, const Vector3& to)
  : x(to.x - from.x), y(to.y - from.y), z(to.z - from.z) {}

// Setters
inline void Vector3::set(const Vector3& v) {
  x = v.x;
  y = v.x;
  z = v.z;
}

inline void Vector3::set(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

inline void Vector3::set(float x, float y) {
  this->x = x;
  this->y = y;
}

inline void Vector3::set(const float* data) {
  x = data[0];
  y = data[1];
  z = data[2];
}

inline void Vector3::set(const Vector3& from, const Vector3& to) {
  x = to.x - from.x;
  y = to.y - from.y;
  z = to.z - from.z;
}

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

inline float& Vector3::operator[](int i) {
  return (&this->x)[i];
}

// Algebra
inline float Vector3::magnitude() const {
  return Math::sqrt(x * x + y * y + z * z);
}

inline float Vector3::squaredMagnitude() const {
  return x * x + y * y + z * z;
}

inline void Vector3::normalize(Vector3* dst) const {
  float m = this->magnitude();

  if (m != 0.0f) {
    dst->x /= m;
    dst->y /= m;
    dst->z /= m;
  }
}

inline Vector3& Vector3::normalize() {
  float m = this->magnitude();

  if (m != 0.0f) {
    x /= m;
    y /= m;
    z /= m;
  }

  return *this;
}

inline void Vector3::negate(Vector3* dst) const {
  dst->set(-x, -y, -z);
}

inline Vector3& Vector3::negate() {
  x = -x;
  y = -y;
  z = -z;
}

inline Vector3& Vector3::cross(const Vector3& v) {
  x = y * v.z - v.y * z;
  y = z * v.x - v.z * x;
  z = x * v.y - v.x * y;
  return *this;
}

inline void Vector3::cross(const Vector3& a, const Vector3& b, Vector3* dst) {
  dst->x = a.y * b.z - b.y * a.z;
  dst->y = a.z * b.x - b.z * a.x;
  dst->z = a.x * b.y - b.x * a.y;
}

inline float Vector3::dot(const Vector3& v) const {
  return x * v.x + y * v.y + z * v.z;
}

inline float Vector3::dot(const Vector3& a, const Vector3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Vector3::angle(const Vector3& to) {
  return angle(*this, to);
}

inline float Vector3::angle(const Vector3& from, const Vector3& to) {
  float dls = dot(from, to) / (from.magnitude() * to.magnitude());

  if (dls < -1.0f) {
    dls = -1.0f;
  } else if (dls > 1.0f) {
    dls = 1.0f;
  }

  return Math::acos(dls);
}

inline void Vector3::scale(float a) {
  x *= a;
  y *= a;
  z *= a;
}

inline void Vector3::add(const Vector3& v) {
  x += v.x;
  y += v.y;
  z += v.z;
}

inline void Vector3::add(float x, float y, float z) {
  this->x += x;
  this->y += y;
  this->z += z;
}

inline void Vector3::add(const Vector3& a, const Vector3& b, Vector3* dst) {
  dst->set(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline void Vector3::subtract(const Vector3& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
}

inline void Vector3::subtract(float x, float y, float z) {
  this->x -= x;
  this->y -= y;
  this->z -= z;
}

inline void Vector3::subtract(const Vector3& a, const Vector3& b, Vector3* dst) {
  dst->set(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline void Vector3::multiply(const Vector3& v) {
  x *= v.x;
  y *= v.y;
  z *= v.z;
}

inline void Vector3::multiply(float x, float y, float z) {
  this->x *= x;
  this->y *= y;
  this->z *= z;
}

inline void Vector3::multiply(const Vector3& a, const Vector3& b, Vector3* dst) {
  dst->set(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline void Vector3::divide(const Vector3& v) {
  x /= v.x;
  y /= v.y;
  z /= v.z;
}

inline void Vector3::divide(float x, float y, float z) {
  this->x /= x;
  this->y /= y;
  this->z /= z;
}

inline void Vector3::divide(const Vector3& a, const Vector3& b, Vector3* dst) {
  dst->set(a.x / b.x, a.y / b.y, a.z / b.z);
}

// Operators
inline Vector3 Vector3::operator+(const Vector3& v) const {
  Vector3 result(*this);
  result.add(v);
  return result;
}

inline Vector3& Vector3::operator+=(const Vector3& v) {
  add(v);
  return *this;
}

inline Vector3 Vector3::operator-(const Vector3& v) const {
  Vector3 result(*this);
  result.subtract(v);
  return result;
}

inline Vector3& Vector3::operator-=(const Vector3& v) {
  subtract(v);
  return *this;
}

inline Vector3 Vector3::operator-() const {
  Vector3 result(*this);
  result.negate();
  return result;
}

inline Vector3 Vector3::operator*(float a) const {
  Vector3 result(*this);
  result.scale(a);
  return result;
}

inline Vector3& Vector3::operator*=(float a) {
  scale(a);
  return *this;
}

inline Vector3 Vector3::operator/(const float a) const {
  return Vector3(x / a, y / a, z / a);
}

inline Vector3& Vector3::operator/=(const float a) {
  scale(1.0f / a);
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

}
