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
  Quaternion(float x, float y, float z, float w);
  Quaternion(const float* data);
  Quaternion(const Matrix4& m);
  Quaternion(const Vector3& axis, float angle);

  Quaternion(const Quaternion& q);
  Quaternion& operator=(const Quaternion& q);

  void set(const Quaternion& q);
  void set(float x, float y, float z, float w);
  void set(const float* data);
  void set(const Matrix4& m);
  void set(const Vector3& axis, float angle);
  void setIdentity();
  void setEulerAngles(const Vector3& eulerAngles);
  void setEulerAngles(float x, float y, float z);
  void setLookAt(const Vector3& direction, const Vector3& up);
  float& operator[](int i);

  inline Quaternion operator*(const Quaternion& q) const;
  inline Quaternion& operator*=(const Quaternion& q);

  Vector3 toEulerAngles() const;
  float magnitude() const;
  float squaredMagnitude() const;
  void normalize(Quaternion *dst) const;
  Quaternion& normalize();
  void conjugate(Quaternion *dst) const;
  Quaternion& conjugate();
  void inverse(Quaternion *dst) const;
  Quaternion& inverse();
  float dot(const Quaternion& q) const;
  static float dot(const Quaternion& a, const Quaternion& b);
  Quaternion& multiply(const Quaternion& q);
  static void multiply(const Quaternion& a, const Quaternion& b, Quaternion* dst);

  void rotatePoint(const Vector3& point, Vector3* dst) const;
  static void rotatePoint(const Quaternion& q, const Vector3& point, Vector3* dst);
  Quaternion& lerp(const Quaternion& b, float t);
  static void lerp(const Quaternion& a, const Quaternion& b, float t, Quaternion* dst);
  Quaternion& slerp(const Quaternion& b, float t);
  static void slerp(const Quaternion& a, const Quaternion& b, float t, Quaternion* dst);
  static void fromEuler(const Vector3& eulerAngles, Quaternion* dst);
  static void fromEuler(float x, float y, float z, Quaternion* dst);
  static void fromRotationMatrix(const Matrix4& m, Quaternion* dst);
  static void fromAxisAngle(const Vector3& axis, float angle, Quaternion *dst);
  static void fromLookAt(const Vector3& direction, const Vector3& up, Quaternion* dst);

  static const Quaternion& identity();
  static const Quaternion& zero();

  friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
};

inline std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
  os << "Quaternion(" << "x: " << q.x << ", y: " << q.y << ", z: " << q.z << ", w: " << q.w << ')';
  return os;
}

}

#include "quaternion.inl"

#endif
