#ifndef BELLUM_VECTOR3_H
#define BELLUM_VECTOR3_H

#include "math.h"
#include <ostream>

namespace bellum {

struct Vector3 {
  float x;
  float y;
  float z;

  Vector3();
  Vector3(float x, float y, float z);
  Vector3(float x, float y);
  Vector3(float a);
  Vector3(const float* data);
  Vector3(const Vector3& from, const Vector3& to);

  Vector3(const Vector3& v);
  Vector3& operator=(const Vector3& v);

  void set(const Vector3& v);
  void set(float x, float y, float z);
  void set(float x, float y);
  void set(const float* data);
  void set(const Vector3& from, const Vector3& to);
  void setMagnitude(float magnitude);
  void setSquaredMagnitude(float sqrMagnitude);
  float& operator[](int32 i);

  float magnitude() const;
  float squaredMagnitude() const;
  void normalize(Vector3* dst) const;
  Vector3& normalize();
  void negate(Vector3* dst) const;
  Vector3& negate();
  Vector3& cross(const Vector3& v);
  static void cross(const Vector3& a, const Vector3& b, Vector3* dst);
  float dot(const Vector3& v) const;
  static float dot(const Vector3& a, const Vector3& b);
  float angle(const Vector3& to);
  static float angle(const Vector3& from, const Vector3& to);
  void scale(float a);
  void add(const Vector3& v);
  void add(float x, float y, float z);
  static void add(const Vector3& a, const Vector3& b, Vector3* dst);
  void subtract(const Vector3& v);
  void subtract(float x, float y, float z);
  static void subtract(const Vector3& a, const Vector3& b, Vector3* dst);
  void multiply(const Vector3& v);
  void multiply(float x, float y, float z);
  static void multiply(const Vector3& a, const Vector3& b, Vector3* dst);
  void divide(const Vector3& v);
  void divide(float x, float y, float z);
  static void divide(const Vector3& a, const Vector3& b, Vector3* dst);

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

  Vector3& clamp(const Vector3& min, const Vector3& max);
  static void clamp(const Vector3& v, const Vector3& min, const Vector3& max, Vector3* dst);
  Vector3& clampMagnitude(float max);
  static void clampMagnitude(const Vector3& v, float max, Vector3* dst);
  static float distance(const Vector3& a, const Vector3& b);
  static float squaredDistance(const Vector3& a, const Vector3& b);
  Vector3& lerp(const Vector3& b, float t);
  static void lerp(const Vector3& a, const Vector3& b, float t, Vector3* dst);
  static Vector3 max(const Vector3& a, const Vector3& b);
  static Vector3 min(const Vector3& a, const Vector3& b);
  Vector3& project(const Vector3& on);
  static void project(const Vector3& v, const Vector3& on, Vector3* dst);
  Vector3& reflect(const Vector3& normal);
  static void reflect(const Vector3& in, const Vector3& normal, Vector3* dst);
  Vector3& slerp(const Vector3& b, float t);
  static void slerp(const Vector3& a, const Vector3& b, float t, Vector3* dst);
  Vector3& rotate(const Vector3& axis, float angle);
  static void rotate(const Vector3& v, const Vector3& axis, float angle, Vector3* dst);

  static const Vector3& back();
  static const Vector3& down();
  static const Vector3& forward();
  static const Vector3& left();
  static const Vector3& right();
  static const Vector3& up();
  static const Vector3& zero();
  static const Vector3& one();

  friend std::ostream& operator<<(std::ostream& os, const Vector3& vector3);
};

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
  : x(a), y(a), z(a) {}

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

inline float& Vector3::operator[](int32 i) {
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

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
  os << "Vector3(x: " << v.x << ", y: " << v.y << ", z: " << v.z << ")";
  return os;
}

}

#endif
