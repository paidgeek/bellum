#ifndef BELLUM_VECTOR3_H
#define BELLUM_VECTOR3_H

#include <cmath>
#include <ostream>

struct Vector3 {
  float x;
  float y;
  float z;

  Vector3();
  Vector3(float x, float y, float z);
  Vector3(float x, float y);

  void set(float x, float y, float z);
  void set(float x, float y);
  void set(const Vector3& v);
  float& operator[](int i);
  float magnitude();
  float sqrMagnitude();
  Vector3 normalized();
  void normalize();

  Vector3 operator+(const Vector3& v);
  Vector3 operator-(const Vector3& v);
  Vector3 operator*(float a);
  Vector3 operator/(float a);
  bool operator==(const Vector3& rhs) const;
  bool operator!=(const Vector3& rhs) const;

  friend std::ostream& operator<<(std::ostream& os, const Vector3& v);

  static Vector3 back();
  static Vector3 down();
  static Vector3 forward();
  static Vector3 left();
  static Vector3 one();
  static Vector3 right();
  static Vector3 up();
  static Vector3 zero();

  static float angle(const Vector3& from, const Vector3& to);
  static Vector3 clampMagnitude(const Vector3& v);
  static Vector3 cross(const Vector3& a, const Vector3& b);
  static float distance(const Vector3& a, const Vector3& b);
  static float dot(const Vector3& a, const Vector3& b);
  static Vector3 lerp(const Vector3& a, const Vector3& b, float t);
  static Vector3 max(const Vector3& a, const Vector3& b);
  static Vector3 min(const Vector3& a, const Vector3& b);
  static Vector3 moveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);
  static Vector3 project(const Vector3& v, const Vector3& normal);
  static Vector3 projectOnPlane(const Vector3& v, const Vector3& normal);
  static Vector3 reflect();
  static Vector3 rotateTowards();
  static Vector3 scale(const Vector3& a, const Vector3& b);
  static Vector3 slerp();
};

inline Vector3 Vector3::back() { return Vector3{0.0f, 0.0f, -1.0f}; }
inline Vector3 Vector3::down() { return Vector3{0.0f, -1.0f, 0.0f}; }
inline Vector3 Vector3::forward() { return Vector3{0.0f, 0.0f, 1.0f}; }
inline Vector3 Vector3::left() { return Vector3{-1.0f, 0.0f, 0.0f}; }
inline Vector3 Vector3::one() { return Vector3{1.0f, 1.0f, 1.0f}; }
inline Vector3 Vector3::right() { return Vector3{1.0f, 0.0f, 0.0f}; }
inline Vector3 Vector3::up() { return Vector3{0.0f, 1.0f, 0.0f}; }
inline Vector3 Vector3::zero() { return Vector3{0.0f, 0.0f, 0.0f}; }

Vector3::Vector3() {}

Vector3::Vector3(float x, float y, float z)
  : x(x), y(y), z(z) {}

Vector3::Vector3(float x, float y)
  : x(x), y(y), z(0.0f) {}

inline void Vector3::set(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

inline void Vector3::set(float x, float y) {
  this->x = x;
  this->y = y;
}

inline void Vector3::set(const Vector3& v) {
  x = v.x;
  y = v.y;
  z = v.z;
}

inline float& Vector3::operator[](int i) {
  return *(&this->x + i);
}

inline float Vector3::magnitude() {
  return std::sqrt(x * x + y * y + z * z);
}

inline float Vector3::sqrMagnitude() {
  return x * x + y * y + z * z;
}

inline Vector3 Vector3::normalized() {
  float m = this->magnitude();

  if (m == 0.0f) {
    return zero();
  }

  return Vector3{x / m, y / m, z / m};
}

inline void Vector3::normalize() {
  float m = this->magnitude();

  if (m == 0.0f) {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
  } else {
    this->x /= m;
    this->y /= m;
    this->z /= m;
  }
}

inline Vector3 Vector3::operator+(const Vector3& v) {
  return Vector3{x + v.x, y + v.y, z + v.z};
}

inline Vector3 Vector3::operator-(const Vector3& v) {
  return Vector3{x - v.x, y - v.y, z - v.z};
}

inline Vector3 Vector3::operator*(float a) {
  return Vector3{x * a, y * a, z * a};
}

inline Vector3 Vector3::operator/(float a) {
  return Vector3{x / a, y / a, z / a};
}

inline bool Vector3::operator==(const Vector3& rhs) const {
  return x == rhs.x && y == rhs.y && z == rhs.z;
}

inline bool Vector3::operator!=(const Vector3& rhs) const {
  return !(rhs == *this);
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
  os << "Vector3(" << "x: " << v.x << " y: " << v.y << " z: " << v.z << ")";
  return os;
}

#endif
