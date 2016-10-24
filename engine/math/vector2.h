#ifndef __BELLUM_VECTOR2_H__
#define __BELLUM_VECTOR2_H__

#include "../common.h"
#include "math.h"

namespace bellum {

struct Vector2 {
  float x;
  float y;

  inline Vector2(float x = 0.0f, float y = 0.0f);
  inline Vector2(const float* data);
  inline Vector2(const Vector2& v);
  inline Vector2& operator=(const Vector2& v);

  inline void set(float x, float y);
  inline void set(const float* data);
  inline void setMagnitude(float magnitude);
  inline void setSquaredMagnitude(float sqrMagnitude);
  inline float& operator[](int32 i);
  inline const float& operator[](int32 i) const;

  inline float magnitude() const;
  inline float squaredMagnitude() const;
  inline Vector2& normalize();
  inline Vector2 normalized() const;

  inline Vector2 operator+(const Vector2& v) const;
  inline Vector2& operator+=(const Vector2& v);
  inline Vector2 operator-(const Vector2& v) const;
  inline Vector2& operator-=(const Vector2& v);
  inline Vector2 operator-() const;
  inline Vector2 operator*(float a) const;
  inline Vector2& operator*=(float a);
  inline Vector2 operator/(float a) const;
  inline Vector2& operator/=(float x);
  inline bool operator==(const Vector2& v) const;
  inline bool operator!=(const Vector2& v) const;

  inline friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
};

// Constructors
Vector2::Vector2(float x, float y)
  : x(x), y(y) {}

Vector2::Vector2(const float* data)
  : x(data[0]), y(data[1]) {}

Vector2::Vector2(const Vector2& v)
  : x(v.x), y(v.y) {}

Vector2& Vector2::operator=(const Vector2& v) {
  x = v.x;
  y = v.y;
  return *this;
}

// Setters
inline void Vector2::set(float x, float y) {
  this->x = x;
  this->y = y;
}

inline void Vector2::set(const float* data) {
  x = data[0];
  y = data[1];
}

inline void Vector2::setMagnitude(float magnitude) {
  this->setSquaredMagnitude(magnitude * magnitude);
}

inline void Vector2::setSquaredMagnitude(float sqrMagnitude) {
  float sm = this->squaredMagnitude();

  if (sm != 0.0f && sm != sqrMagnitude) {
    float s = Math::sqrt(sqrMagnitude / sm);
    x *= s;
    y *= s;
  }
}

inline float& Vector2::operator[](int32 i) {
  return *(&this->x + i);
}

inline const float& Vector2::operator[](int32 i) const {
  return *(&this->x + i);
}

// Properties
inline float Vector2::magnitude() const {
  return Math::sqrt(x * x + y * y);
}

inline float Vector2::squaredMagnitude() const {
  return x * x + y * y ;
}

inline Vector2& Vector2::normalize() {
  float m = magnitude();

  if (m != 0.0f) {
    x /= m;
    y /= m;
  }

  return *this;
}

inline Vector2 Vector2::normalized() const {
  float m = magnitude();

  if (m != 0.0f) {
    return {x / m, y / m};
  }

  return *this;
}

// Operators
inline Vector2 Vector2::operator+(const Vector2& v) const {
  return {x + v.x, y + v.y};
}

inline Vector2& Vector2::operator+=(const Vector2& v) {
  x += v.x;
  y += v.y;
  return *this;
}

inline Vector2 Vector2::operator-(const Vector2& v) const {
  return {x - v.x, y - v.y};
}

inline Vector2& Vector2::operator-=(const Vector2& v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

inline Vector2 Vector2::operator-() const {
  return {-x, -y};
}

inline Vector2 Vector2::operator*(float a) const {
  return {x * a, y * a};
}

inline Vector2& Vector2::operator*=(float a) {
  x *= a;
  y *= a;
  return *this;
}

inline Vector2 Vector2::operator/(const float a) const {
  return {x / a, y / a};
}

inline Vector2& Vector2::operator/=(const float a) {
  x /= a;
  y /= a;
  return *this;
}

inline bool Vector2::operator==(const Vector2& v) const {
  return x == v.x && y == v.y;
}

inline bool Vector2::operator!=(const Vector2& v) const {
  return x != v.x || y != v.y;
}

inline Vector2 operator*(float a, const Vector2& v) {
  return {
    v.x * a,
    v.x * a,
  };
}

inline std::ostream& operator<<(std::ostream& os, const Vector2& v) {
  os << "Vector3(x: " << v.x << ", y: " << v.y << ")";
  return os;
}

}

#endif
