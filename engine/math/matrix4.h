#ifndef BELLUM_MATRIX4_H
#define BELLUM_MATRIX4_H

#include <ostream>
#include <cstring>
#include <array>
#include "math.h"
#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"
#include "plane.h"

namespace bellum {

struct Matrix4 {
  float data[16];

  inline Matrix4();
  inline Matrix4(const float* data);
  inline Matrix4(const std::array<float, 16>& data);
  inline Matrix4(float m11, float m12, float m13, float m14,
                 float m21, float m22, float m23, float m24,
                 float m31, float m32, float m33, float m34,
                 float m41, float m42, float m43, float m44);
  inline Matrix4(std::array<std::array<float, 4>, 4> data);
  inline Matrix4(const Matrix4& m);
  inline Matrix4& operator=(const Matrix4& m);

  inline void set(const float* data);
  inline void set(const std::array<float, 16>& data);
  inline void set(float m11, float m12, float m13, float m14,
                  float m21, float m22, float m23, float m24,
                  float m31, float m32, float m33, float m34,
                  float m41, float m42, float m43, float m44);
  inline void set(std::array<std::array<float, 4>, 4> data);
  inline float get(int32 row, int32 column) const;
  inline void set(int32 row, int32 column, float value);
  inline void set(int32 i, float value);
  inline float& operator[](size_t i);
  inline const float& operator[](size_t i) const;
  inline void clear();
  inline void setTransformation(const Vector3& translation,
                                const Quaternion& rotation,
                                const Vector3& scale);

  inline float determinant() const;
  inline Matrix4& inverse();
  inline Matrix4 inversed() const;
  inline Matrix4& negate();
  inline Matrix4 negated() const;
  inline Matrix4& transpose();
  inline Matrix4 transposed() const;
  inline bool isIdentity() const;

  inline Vector4 getColumn(int32 i) const;
  inline Vector4 getRow(int32 i) const;

  inline static Vector3 multiplyPoint(const Matrix4& m, const Vector3& point);
  inline static Vector3 multiplyVector(const Matrix4& m, const Vector3& v);
  inline static Vector3 multiplyVector(const Matrix4& m, const Vector4& v);
  inline static Vector4 multiplyVector4(const Matrix4& m, const Vector4& v);

  inline Matrix4 operator+(const Matrix4& m) const;
  inline Matrix4 operator-(const Matrix4& m) const;
  inline Matrix4& operator+=(const Matrix4& m);
  inline Matrix4& operator-=(const Matrix4& m);
  inline Matrix4 operator-() const;
  inline Matrix4 operator*(const Matrix4& m) const;
  inline Matrix4& operator*=(const Matrix4& m);
  inline Matrix4 operator+(float a) const;
  inline Matrix4& operator+=(float a);
  inline Matrix4 operator-(float a) const;
  inline Matrix4& operator-=(float a);
  inline Matrix4 operator*(float a) const;
  inline Matrix4& operator*=(float a);
  inline Matrix4 operator/(float a) const;
  inline Matrix4& operator/=(float a);

  inline static Matrix4 makeOrthographic(float left, float right,
                                         float bottom, float top,
                                         float near, float far);
  inline static Matrix4 makePerspective(float fov, float aspect, float near, float far);
  inline static Matrix4 makeTransformation(const Vector3& translation,
                                           const Quaternion& rotation,
                                           const Vector3& scale);
  inline static Matrix4
  makeLookAt(const Vector3& position, const Vector3& target, const Vector3& up);
  inline static Matrix4 makeBillboard(const Vector3& position,
                                      const Vector3& cameraPosition,
                                      const Vector3& cameraUp,
                                      const Vector3& cameraForward);
  inline static Matrix4 makeReflection(const Plane& plane);
  inline static Matrix4 makeTranslation(const Vector3& translation);
  inline static Matrix4 makeTranslation(float x, float y, float z);
  inline static Matrix4 makeScale(const Vector3& scale);
  inline static Matrix4 makeScale(float x, float y, float z);
  inline static Matrix4
  makeRotation(const Vector3& forward, const Vector3& up, const Vector3& right);
  inline static Matrix4 makeRotation(const Vector3& forward, const Vector3& up);
  inline static Matrix4 makeRotation(const Quaternion& q);
  inline static Matrix4 makeAxisRotation(const Vector3& axis, float angle);
  inline static Matrix4 makeEulerRotation(const Vector3& euler);
  inline static Matrix4 makeEulerRotation(float x, float y, float z);
  inline static Matrix4 makeRotationAroundX(float angle);
  inline static Matrix4 makeRotationAroundY(float angle);
  inline static Matrix4 makeRotationAroundZ(float angle);

  inline static const Matrix4& identity();
  inline static const Matrix4& zero();

  friend std::ostream& operator<<(std::ostream& os, const Matrix4& m);
};

// Constructors
inline Matrix4::Matrix4() {
  *this = identity();
}

inline Matrix4::Matrix4(const float* data) {
  this->set(data);
}

inline Matrix4::Matrix4(const std::array<float, 16>& data) {
  this->set(data);
}

inline Matrix4::Matrix4(float m11, float m12, float m13, float m14,
                        float m21, float m22, float m23, float m24,
                        float m31, float m32, float m33, float m34,
                        float m41, float m42, float m43, float m44) {
  this->set(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}

inline Matrix4::Matrix4(std::array<std::array<float, 4>, 4> data) {
  this->set(data);
}

inline Matrix4::Matrix4(const Matrix4& m) {
  std::memcpy(data, m.data, 16);
}

inline Matrix4& Matrix4::operator=(const Matrix4& m) {
  std::memcpy(data, m.data, 16);
  return *this;
}

// Setters and getters
inline void Matrix4::set(const float* data) {
  std::memcpy(this->data, data, 16);
}

inline void Matrix4::set(const std::array<float, 16>& data) {
  std::memcpy(this->data, data.data(), 16);
}

inline void Matrix4::set(float m11, float m12, float m13, float m14,
                         float m21, float m22, float m23, float m24,
                         float m31, float m32, float m33, float m34,
                         float m41, float m42, float m43, float m44) {
  data[0] = m11;
  data[1] = m21;
  data[2] = m31;
  data[3] = m41;
  data[4] = m12;
  data[5] = m22;
  data[6] = m32;
  data[7] = m42;
  data[8] = m13;
  data[9] = m23;
  data[10] = m33;
  data[11] = m43;
  data[12] = m14;
  data[13] = m24;
  data[14] = m34;
  data[15] = m44;
}

inline void Matrix4::set(std::array<std::array<float, 4>, 4> data) {
  std::memcpy(this->data, data.data(), 16);
}

inline float Matrix4::get(int32 row, int32 column) const {
  return data[column + (row << 2)];
}

inline void Matrix4::set(int32 row, int32 column, float value) {
  data[column + (row << 2)] = value;
}

inline void Matrix4::set(int32 i, float value) {
  data[i] = value;
}

inline float& Matrix4::operator[](size_t i) {
  return data[i];
}

inline const float& Matrix4::operator[](size_t i) const {
  return data[i];
}

inline void Matrix4::clear() {
  std::memset(data, 0, 16);
}

inline void Matrix4::setTransformation(const Vector3& translation,
                                       const Quaternion& rotation,
                                       const Vector3& scale) {
  *this = makeTransformation(translation, rotation, scale);
}

// Algebra
inline float Matrix4::determinant() const {
  float a0 = data[0] * data[5] - data[1] * data[4];
  float a1 = data[0] * data[6] - data[2] * data[4];
  float a2 = data[0] * data[7] - data[3] * data[4];
  float a3 = data[1] * data[6] - data[2] * data[5];
  float a4 = data[1] * data[7] - data[3] * data[5];
  float a5 = data[2] * data[7] - data[3] * data[6];
  float b0 = data[8] * data[13] - data[9] * data[12];
  float b1 = data[8] * data[14] - data[10] * data[12];
  float b2 = data[8] * data[15] - data[11] * data[12];
  float b3 = data[9] * data[14] - data[10] * data[13];
  float b4 = data[9] * data[15] - data[11] * data[13];
  float b5 = data[10] * data[15] - data[11] * data[14];

  return a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
}

inline Matrix4& Matrix4::inverse() {
  Matrix4 inv = inversed();
  std::memcpy(data, inv.data, 16);
  return *this;
}

inline Matrix4 Matrix4::inversed() const {
  float a0 = data[0] * data[5] - data[1] * data[4];
  float a1 = data[0] * data[6] - data[2] * data[4];
  float a2 = data[0] * data[7] - data[3] * data[4];
  float a3 = data[1] * data[6] - data[2] * data[5];
  float a4 = data[1] * data[7] - data[3] * data[5];
  float a5 = data[2] * data[7] - data[3] * data[6];
  float b0 = data[8] * data[13] - data[9] * data[12];
  float b1 = data[8] * data[14] - data[10] * data[12];
  float b2 = data[8] * data[15] - data[11] * data[12];
  float b3 = data[9] * data[14] - data[10] * data[13];
  float b4 = data[9] * data[15] - data[11] * data[13];
  float b5 = data[10] * data[15] - data[11] * data[14];

  float d = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

  Matrix4 inverse;
  inverse[0] = data[5] * b5 - data[6] * b4 + data[7] * b3;
  inverse[1] = -data[1] * b5 + data[2] * b4 - data[3] * b3;
  inverse[2] = data[13] * a5 - data[14] * a4 + data[15] * a3;
  inverse[3] = -data[9] * a5 + data[10] * a4 - data[11] * a3;

  inverse[4] = -data[4] * b5 + data[6] * b2 - data[7] * b1;
  inverse[5] = data[0] * b5 - data[2] * b2 + data[3] * b1;
  inverse[6] = -data[12] * a5 + data[14] * a2 - data[15] * a1;
  inverse[7] = data[8] * a5 - data[10] * a2 + data[11] * a1;

  inverse[8] = data[4] * b4 - data[5] * b2 + data[7] * b0;
  inverse[9] = -data[0] * b4 + data[1] * b2 - data[3] * b0;
  inverse[10] = data[12] * a4 - data[13] * a2 + data[15] * a0;
  inverse[11] = -data[8] * a4 + data[9] * a2 - data[11] * a0;

  inverse[12] = -data[4] * b3 + data[5] * b1 - data[6] * b0;
  inverse[13] = data[0] * b3 - data[1] * b1 + data[2] * b0;
  inverse[14] = -data[12] * a3 + data[13] * a1 - data[14] * a0;
  inverse[15] = data[8] * a3 - data[9] * a1 + data[10] * a0;

  return inverse / d;
}

inline Matrix4& Matrix4::negate() {
  data[0] = -data[0];
  data[1] = -data[1];
  data[2] = -data[2];
  data[3] = -data[3];
  data[4] = -data[4];
  data[5] = -data[5];
  data[6] = -data[6];
  data[7] = -data[7];
  data[8] = -data[8];
  data[9] = -data[9];
  data[10] = -data[10];
  data[11] = -data[11];
  data[12] = -data[12];
  data[13] = -data[13];
  data[14] = -data[14];
  data[15] = -data[15];
}

inline Matrix4 Matrix4::negated() const {
  return {
    -data[0],
    -data[1],
    -data[2],
    -data[3],
    -data[4],
    -data[5],
    -data[6],
    -data[7],
    -data[8],
    -data[9],
    -data[10],
    -data[11],
    -data[12],
    -data[13],
    -data[14],
    -data[15]
  };
}

inline Matrix4& Matrix4::transpose() {
  float t[16] = {
    data[0], data[4], data[8], data[12],
    data[1], data[5], data[9], data[13],
    data[2], data[6], data[10], data[14],
    data[3], data[7], data[11], data[15]
  };
  std::memcpy(data, t, 16);
}

inline Matrix4 Matrix4::transposed() const {
  float t[16] = {
    data[0], data[4], data[8], data[12],
    data[1], data[5], data[9], data[13],
    data[2], data[6], data[10], data[14],
    data[3], data[7], data[11], data[15]
  };
  return {t};
}

inline bool Matrix4::isIdentity() const {
  return std::memcmp(data, identity().data, 16) == 0;
}

inline Vector4 Matrix4::getColumn(int32 i) const {
  return {get(0, i), get(1, i), get(2, i), get(3, i)};
}

inline Vector4 Matrix4::getRow(int32 i) const {
  return {get(i, 0), get(i, 1), get(i, 2), get(i, 3)};
}

inline Vector3 Matrix4::multiplyPoint(const Matrix4& m, const Vector3& point) {
  return multiplyVector(m, Vector4{point.x, point.y, point.z, 1.0f});
}

inline Vector3 Matrix4::multiplyVector(const Matrix4& m, const Vector3& v) {
  return multiplyVector(m, {v.x, v.y, v.z, 0.0f});
}

inline Vector3 Matrix4::multiplyVector(const Matrix4& m, const Vector4& v) {
  return {
    v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12],
    v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13],
    v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14]
  };
}

inline Vector4 Matrix4::multiplyVector4(const Matrix4& m, const Vector4& v) {
  return {
    v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3] * m[12],
    v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3] * m[13],
    v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14],
    v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3] * m[15]
  };
}

// Operators
inline Matrix4 Matrix4::operator+(const Matrix4& m) const {
  return {
    m.data[0] + data[0],
    m.data[1] + data[1],
    m.data[2] + data[2],
    m.data[3] + data[3],
    m.data[4] + data[4],
    m.data[5] + data[5],
    m.data[6] + data[6],
    m.data[7] + data[7],
    m.data[8] + data[8],
    m.data[9] + data[9],
    m.data[10] + data[10],
    m.data[11] + data[11],
    m.data[12] + data[12],
    m.data[13] + data[13],
    m.data[14] + data[14],
    m.data[15] + data[15]
  };
}

inline Matrix4 Matrix4::operator-(const Matrix4& m) const {
  return {
    m.data[0] - data[0],
    m.data[1] - data[1],
    m.data[2] - data[2],
    m.data[3] - data[3],
    m.data[4] - data[4],
    m.data[5] - data[5],
    m.data[6] - data[6],
    m.data[7] - data[7],
    m.data[8] - data[8],
    m.data[9] - data[9],
    m.data[10] - data[10],
    m.data[11] - data[11],
    m.data[12] - data[12],
    m.data[13] - data[13],
    m.data[14] - data[14],
    m.data[15] - data[15]
  };
}

inline Matrix4& Matrix4::operator+=(const Matrix4& m) {
  *this = *this + m;
  return *this;
}

inline Matrix4& Matrix4::operator-=(const Matrix4& m) {
  *this = *this - m;
  return *this;
}

inline Matrix4 Matrix4::operator-() const {
  return {
    -data[0],
    -data[1],
    -data[2],
    -data[3],
    -data[4],
    -data[5],
    -data[6],
    -data[7],
    -data[8],
    -data[9],
    -data[10],
    -data[11],
    -data[12],
    -data[13],
    -data[14],
    -data[15]
  };
}

inline Matrix4 Matrix4::operator*(const Matrix4& m) const {
  return {
    data[0] * m[0] + data[4] * m[1] + data[8] * m[2] + data[12] * m[3],
    data[1] * m[0] + data[5] * m[1] + data[9] * m[2] + data[13] * m[3],
    data[2] * m[0] + data[6] * m[1] + data[10] * m[2] + data[14] * m[3],
    data[3] * m[0] + data[7] * m[1] + data[11] * m[2] + data[15] * m[3],
    data[0] * m[4] + data[4] * m[5] + data[8] * m[6] + data[12] * m[7],
    data[1] * m[4] + data[5] * m[5] + data[9] * m[6] + data[13] * m[7],
    data[2] * m[4] + data[6] * m[5] + data[10] * m[6] + data[14] * m[7],
    data[3] * m[4] + data[7] * m[5] + data[11] * m[6] + data[15] * m[7],
    data[0] * m[8] + data[4] * m[9] + data[8] * m[10] + data[12] * m[11],
    data[1] * m[8] + data[5] * m[9] + data[9] * m[10] + data[13] * m[11],
    data[2] * m[8] + data[6] * m[9] + data[10] * m[10] + data[14] * m[11],
    data[3] * m[8] + data[7] * m[9] + data[11] * m[10] + data[15] * m[11],
    data[0] * m[12] + data[4] * m[13] + data[8] * m[14] + data[12] * m[15],
    data[1] * m[12] + data[5] * m[13] + data[9] * m[14] + data[13] * m[15],
    data[2] * m[12] + data[6] * m[13] + data[10] * m[14] + data[14] * m[15],
    data[3] * m[12] + data[7] * m[13] + data[11] * m[14] + data[15] * m[15]
  };
}

inline Matrix4& Matrix4::operator*=(const Matrix4& m) {
  *this = *this * m;
  return *this;
}

inline Matrix4 Matrix4::operator+(float a) const {
  return {
    data[0] + a,
    data[1] + a,
    data[2] + a,
    data[3] + a,
    data[4] + a,
    data[5] + a,
    data[6] + a,
    data[7] + a,
    data[8] + a,
    data[9] + a,
    data[10] + a,
    data[11] + a,
    data[12] + a,
    data[13] + a,
    data[14] + a,
    data[15] + a
  };
}

inline Matrix4& Matrix4::operator+=(float a) {
  *this = *this + a;
  return *this;
}

inline Matrix4 Matrix4::operator-(float a) const {
  return {
    data[0] - a,
    data[1] - a,
    data[2] - a,
    data[3] - a,
    data[4] - a,
    data[5] - a,
    data[6] - a,
    data[7] - a,
    data[8] - a,
    data[9] - a,
    data[10] - a,
    data[11] - a,
    data[12] - a,
    data[13] - a,
    data[14] - a,
    data[15] - a
  };
}

inline Matrix4& Matrix4::operator-=(float a) {
  *this = *this - a;
  return *this;
}

inline Matrix4 Matrix4::operator*(float a) const {
  return {
    data[0] * a,
    data[1] * a,
    data[2] * a,
    data[3] * a,
    data[4] * a,
    data[5] * a,
    data[6] * a,
    data[7] * a,
    data[8] * a,
    data[9] * a,
    data[10] * a,
    data[11] * a,
    data[12] * a,
    data[13] * a,
    data[14] * a,
    data[15] * a
  };
}

inline Matrix4& Matrix4::operator*=(float a) {
  *this = *this * a;
  return *this;
}

inline Matrix4 Matrix4::operator/(float a) const {
  return {
    data[0] / a,
    data[1] / a,
    data[2] / a,
    data[3] / a,
    data[4] / a,
    data[5] / a,
    data[6] / a,
    data[7] / a,
    data[8] / a,
    data[9] / a,
    data[10] / a,
    data[11] / a,
    data[12] / a,
    data[13] / a,
    data[14] / a,
    data[15] / a
  };
}

inline Matrix4& Matrix4::operator/=(float a) {
  *this = *this / a;
  return *this;
}

// Factory methods
inline Matrix4 Matrix4::makeOrthographic(float left, float right,
                                         float bottom, float top,
                                         float near, float far) {
  Matrix4 result;
  result.clear();
  result[0] = 2.0f / (right - left);
  result[5] = 2.0f / (top - bottom);
  result[12] = (left + right) / (left - right);
  result[10] = 1.0f / (near - far);
  result[13] = (top + bottom) / (bottom - top);
  result[14] = near / (near - far);
  result[15] = 1.0f;
  return result;
}

inline Matrix4 Matrix4::makePerspective(float fov, float aspect, float near, float far) {
  float f = 1.0f / (far - near);
  float theta = Math::kDegToRad * fov / 2.0f;

  float d = Math::tan(theta);
  float m = 1.0f / d;

  Matrix4 result;
  result.clear();
  result.data[0] = (1.0f / aspect) * m;
  result.data[5] = m;
  result.data[10] = f * (-far - near);
  result.data[11] = -1.0f;
  result.data[14] = -2.0f * far * near * f;

  return result;
}

inline Matrix4 Matrix4::makeTransformation(const Vector3& translation,
                                           const Quaternion& rotation,
                                           const Vector3& scale) {
  return makeTranslation(translation) * makeRotation(rotation) * makeScale(scale);
}

inline Matrix4 Matrix4::makeLookAt(const Vector3& position,
                                   const Vector3& target,
                                   const Vector3& up) {
  Vector3 upNorm = up.normalized();
  Vector3 zaxis = (position - target).normalized();
  Vector3 xaxis = Vector3::cross(up, zaxis).normalized();
  Vector3 yaxis = Vector3::cross(zaxis, xaxis).normalized();

  return {
    xaxis.x,
    yaxis.x,
    zaxis.x,
    0.0f,
    xaxis.y,
    yaxis.y,
    zaxis.y,
    0.0f,
    xaxis.z,
    yaxis.z,
    zaxis.z,
    0.0f,
    -Vector3::dot(xaxis, position),
    -Vector3::dot(yaxis, position),
    -Vector3::dot(zaxis, position),
    1.0f
  };
}

inline Matrix4 Matrix4::makeBillboard(const Vector3& position,
                                      const Vector3& cameraPosition,
                                      const Vector3& cameraUp,
                                      const Vector3& cameraForward) {
  Matrix4 result{};
  result[3] = position.x;
  result[7] = position.y;
  result[11] = position.z;

  Matrix4 lookAt = makeLookAt(position, cameraPosition, cameraUp);
  result[0] = lookAt[0];
  result[1] = lookAt[4];
  result[2] = lookAt[8];
  result[4] = lookAt[1];
  result[5] = lookAt[5];
  result[6] = lookAt[9];
  result[8] = lookAt[2];
  result[9] = lookAt[6];
  result[10] = lookAt[10];

  return result;
}

inline Matrix4 Matrix4::makeReflection(const Plane& plane) {
  Vector3 n(plane.normal);
  float k = -2.0f * plane.distance;

  Matrix4 result{};

  result[0] -= 2.0f * n.x * n.x;
  result[5] -= 2.0f * n.y * n.y;
  result[10] -= 2.0f * n.z * n.z;
  result[1] = result[4] = -2.0f * n.x * n.y;
  result[2] = result[8] = -2.0f * n.x * n.z;
  result[6] = result[9] = -2.0f * n.y * n.z;
  result[3] = k * n.x;
  result[7] = k * n.y;
  result[11] = k * n.z;

  return result;
}

inline Matrix4 Matrix4::makeTranslation(const Vector3& translation) {
  return makeTranslation(translation.x, translation.y, translation.z);
}

inline Matrix4 Matrix4::makeTranslation(float x, float y, float z) {
  Matrix4 result{};
  result[12] = x;
  result[13] = y;
  result[14] = z;
  return result;
}

inline Matrix4 Matrix4::makeScale(const Vector3& scale) {
  return makeScale(scale.x, scale.y, scale.z);
}

inline Matrix4 Matrix4::makeScale(float x, float y, float z) {
  Matrix4 result{};
  result[0] = x;
  result[5] = y;
  result[10] = z;
  return result;
}

inline Matrix4 Matrix4::makeRotation(const Vector3& forward,
                                     const Vector3& up,
                                     const Vector3& right) {
  Matrix4 result;
  result.clear();
  result.set(0, 0, right.x);
  result.set(0, 1, right.y);
  result.set(0, 2, right.z);
  result.set(1, 0, up.x);
  result.set(1, 1, up.y);
  result.set(1, 2, up.z);
  result.set(2, 0, forward.x);
  result.set(2, 1, forward.y);
  result.set(2, 2, forward.z);
  result.set(3, 3, 1.0f);
  return result;
}

inline Matrix4 Matrix4::makeRotation(const Vector3& forward, const Vector3& up) {
  Vector3 f = forward.normalized();
  Vector3 r = Vector3::cross(up.normalized(), f);
  Vector3 u = Vector3::cross(f, r);

  return makeRotation(f, u, r);
}

inline Matrix4 Matrix4::makeRotation(const Quaternion& q) {
  float x2 = q.x + q.x;
  float y2 = q.y + q.y;
  float z2 = q.z + q.z;

  float xx2 = q.x * x2;
  float yy2 = q.y * y2;
  float zz2 = q.z * z2;
  float xy2 = q.x * y2;
  float xz2 = q.x * z2;
  float yz2 = q.y * z2;
  float wx2 = q.w * x2;
  float wy2 = q.w * y2;
  float wz2 = q.w * z2;

  return {
    1.0f - yy2 - zz2,
    xy2 + wz2,
    xz2 - wy2,
    0.0f,
    xy2 - wz2,
    1.0f - xx2 - zz2,
    yz2 + wx2,
    0.0f,
    xz2 + wy2,
    yz2 - wx2,
    1.0f - xx2 - yy2,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f
  };
}

inline Matrix4 Matrix4::makeAxisRotation(const Vector3& axis, float angle) {
  float x = axis.x;
  float y = axis.y;
  float z = axis.z;

  float n = x * x + y * y + z * z;

  if (n != 1.0f) {
    n = Math::sqrt(n);

    if (n > 0.000001f) {
      n = 1.0f / n;
      x *= n;
      y *= n;
      z *= n;
    }
  }

  float c = Math::cos(angle);
  float s = Math::sin(angle);

  float t = 1.0f - c;
  float tx = t * x;
  float ty = t * y;
  float tz = t * z;
  float txy = tx * y;
  float txz = tx * z;
  float tyz = ty * z;
  float sx = s * x;
  float sy = s * y;
  float sz = s * z;

  return {
    c + tx * x,
    txy + sz,
    txz - sy,
    0.0f,
    txy - sz,
    c + ty * y,
    tyz + sx,
    0.0f,
    txz + sy,
    tyz - sx,
    c + tz * z,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f
  };
}

inline Matrix4 Matrix4::makeEulerRotation(const Vector3& euler) {
  return makeEulerRotation(euler.x, euler.y, euler.z);
}

inline Matrix4 Matrix4::makeEulerRotation(float x, float y, float z) {
  return makeRotationAroundX(x) * makeRotationAroundY(y) * makeRotationAroundZ(z);
}

inline Matrix4 Matrix4::makeRotationAroundX(float angle) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  Matrix4 result;
  result.clear();
  result[5] = cos;
  result[6] = sin;
  result[9] = -sin;
  result[10] = cos;

  return result;
}

inline Matrix4 Matrix4::makeRotationAroundY(float angle) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  Matrix4 result;
  result.clear();
  result[0] = cos;
  result[2] = -sin;
  result[8] = sin;
  result[10] = cos;

  return result;
}

inline Matrix4 Matrix4::makeRotationAroundZ(float angle) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  Matrix4 result;
  result.clear();
  result[0] = cos;
  result[1] = sin;
  result[4] = -sin;
  result[5] = cos;

  return result;
}

// Singletons
inline const Matrix4& Matrix4::identity() {
  static Matrix4 value{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  return value;
}

inline const Matrix4& Matrix4::zero() {
  static Matrix4 value{};
  return value;
}

inline std::ostream& operator<<(std::ostream& os, const Matrix4& m) {
  os << "Matrix4(" << '\n';
  os << " " << m.get(0, 0) << ", " << m.get(0, 1) << ", " << m.get(0, 2) << ", " << m.get(0, 3)
     << ",\n";
  os << " " << m.get(1, 0) << ", " << m.get(1, 1) << ", " << m.get(1, 2) << ", " << m.get(1, 3)
     << ",\n";
  os << " " << m.get(2, 0) << ", " << m.get(2, 1) << ", " << m.get(2, 2) << ", " << m.get(2, 3)
     << ",\n";
  os << " " << m.get(3, 0) << ", " << m.get(3, 1) << ", " << m.get(3, 2) << ", " << m.get(3, 3)
     << ",\n";
  os << ')';
  return os;
}

}

#endif
