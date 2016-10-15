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
  float& operator[](int i);

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

inline Vector3 operator*(float a, const Vector3& v);

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
  os << "Vector3(x: " << v.x << ", y: " << v.y << ", z: " << v.z << ")";
  return os;
}

}

#include "vector3.inl"

#endif
