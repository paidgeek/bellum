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

  inline void set(const Matrix4& m);
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

  inline float determinant() const;
  inline Matrix4& inverse();
  inline void inverse(Matrix4& dst) const;
  inline Matrix4& negate();
  inline void negate(Matrix4& dst) const;
  inline Matrix4& transpose();
  inline void transpose(Matrix4& dst) const;

  inline static void add(const Matrix4& m, float a, Matrix4& dst);
  inline static void add(const Matrix4& a, const Matrix4& b, Matrix4& dst);
  inline static void subtract(const Matrix4& m, float a, Matrix4& dst);
  inline static void subtract(const Matrix4& a, const Matrix4& b, Matrix4& dst);
  inline static void multiply(const Matrix4& m, float a, Matrix4& dst);
  inline static void multiply(const Matrix4& a, const Matrix4& b, Matrix4& dst);
  inline static void translate(const Matrix4& m, const Vector3& translation, Matrix4& dst);
  inline static void translate(const Matrix4& m, float x, float y, float z, Matrix4& dst);
  inline static void scale(const Matrix4& m, float a, Matrix4& dst);
  inline static void scale(const Matrix4& m, const Vector3& scale, Matrix4& dst);
  inline static void scale(const Matrix4& m, float x, float y, float z, Matrix4& dst);
  inline static void rotate(const Matrix4& m, const Quaternion& rotation, Matrix4& dst);
  inline static void rotateAxis(const Matrix4& m, const Vector3& axis, float angle, Matrix4& dst);
  inline static void rotateAroundX(const Matrix4& m, float angle, Matrix4& dst);
  inline static void rotateAroundY(const Matrix4& m, float angle, Matrix4& dst);
  inline static void rotateAroundZ(const Matrix4& m, float angle, Matrix4& dst);
  inline static void transformPoint(const Matrix4& m, const Vector3& point, Vector3& dst);
  inline static void transformVector(const Matrix4& m, const Vector3& v, Vector3& dst);
  inline static void transformVector(const Matrix4& m, const Vector4& v, Vector3& dst);
  inline static void transformVector(const Matrix4& m, const Vector4& v, Vector4& dst);

  inline Matrix4 operator+(const Matrix4& m) const;
  inline Matrix4 operator-(const Matrix4& m) const;
  inline Matrix4& operator+=(const Matrix4& m);
  inline Matrix4& operator-=(const Matrix4& m);
  inline Matrix4 operator-() const;
  inline Matrix4 operator*(const Matrix4& m) const;
  inline Matrix4& operator*=(const Matrix4& m);

  static void makeIdentity(Matrix4& dst);
  static void makeLookAt(const Vector3& position, const Vector3& target, const Vector3& up,
                         Matrix4& dst);
  static void makeOrthographic(float left, float right,
                               float bottom, float top,
                               float near, float far,
                               Matrix4& dst);
  static void makePerspective(float fov, float aspectRatio, float near, float far, Matrix4& dst);
  static void makeBillboard(const Vector3& position,
                            const Vector3& cameraPosition,
                            const Vector3& cameraUp,
                            const Vector3& cameraForward,
                            Matrix4& dst);
  static void makeReflection(const Plane& plane, Matrix4& dst);
  static void makeTranslation(const Vector3& translation, Matrix4& dst);
  static void makeTranslation(float x, float y, float z, Matrix4& dst);
  static void makeScale(const Vector3& scale, Matrix4& dst);
  static void makeScale(float x, float y, float z, Matrix4& dst);
  static void makeRotation(const Vector3& forward, const Vector3& up, const Vector3& right,
                           Matrix4& dst);
  static void makeRotation(const Vector3& forward, const Vector3& up, Matrix4& dst);
  static void makeRotation(const Quaternion& q, Matrix4& dst);
  static void makeAxisRotation(const Vector3& axis, float angle, Matrix4& dst);
  static void makeEulerRotation(const Vector3& eulerAngles, Matrix4& dst);
  static void makeEulerRotation(float x, float y, float z, Matrix4& dst);
  static void makeRotationAroundX(float angle, Matrix4& dst);
  static void makeRotationAroundY(float angle, Matrix4& dst);
  static void makeRotationAroundZ(float angle, Matrix4& dst);

  inline static const Matrix4& identity();
  inline static const Matrix4& zero();

  friend std::ostream& operator<<(std::ostream& os, const Matrix4& m);
};

// Constructors
Matrix4::Matrix4() {
  *this = identity();
}

Matrix4::Matrix4(const float* data) {
  this->set(data);
}

Matrix4::Matrix4(const std::array<float, 16>& data) {
  this->set(data);
}

Matrix4::Matrix4(float m11, float m12, float m13, float m14,
                 float m21, float m22, float m23, float m24,
                 float m31, float m32, float m33, float m34,
                 float m41, float m42, float m43, float m44) {
  this->set(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}

Matrix4::Matrix4(std::array<std::array<float, 4>, 4> data) {
  this->set(data);
}

Matrix4::Matrix4(const Matrix4& m) {
  this->set(m);
}

Matrix4& Matrix4::operator=(const Matrix4& m) {
  this->set(m);
  return *this;
}

// Setters and getters
inline void Matrix4::set(const Matrix4& m) {
  std::memcpy(this->data, m.data, 16);
}

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

float& Matrix4::operator[](size_t i) {
  return data[i];
}

const float& Matrix4::operator[](size_t i) const {
  return data[i];
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
  this->inverse(*this);
}

inline void Matrix4::inverse(Matrix4& dst) const {
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

  multiply(inverse, 1.0f / d, dst);
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

inline void Matrix4::negate(Matrix4& dst) const {
  dst.data[0] = -data[0];
  dst.data[1] = -data[1];
  dst.data[2] = -data[2];
  dst.data[3] = -data[3];
  dst.data[4] = -data[4];
  dst.data[5] = -data[5];
  dst.data[6] = -data[6];
  dst.data[7] = -data[7];
  dst.data[8] = -data[8];
  dst.data[9] = -data[9];
  dst.data[10] = -data[10];
  dst.data[11] = -data[11];
  dst.data[12] = -data[12];
  dst.data[13] = -data[13];
  dst.data[14] = -data[14];
  dst.data[15] = -data[15];
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

inline void Matrix4::transpose(Matrix4& dst) const {
  float t[16] = {
    data[0], data[4], data[8], data[12],
    data[1], data[5], data[9], data[13],
    data[2], data[6], data[10], data[14],
    data[3], data[7], data[11], data[15]
  };
  std::memcpy(dst.data, t, 16);
}

inline void Matrix4::add(const Matrix4& m, float a, Matrix4& dst) {
  dst[0] = m.data[0] + a;
  dst[1] = m.data[1] + a;
  dst[2] = m.data[2] + a;
  dst[3] = m.data[3] + a;
  dst[4] = m.data[4] + a;
  dst[5] = m.data[5] + a;
  dst[6] = m.data[6] + a;
  dst[7] = m.data[7] + a;
  dst[8] = m.data[8] + a;
  dst[9] = m.data[9] + a;
  dst[10] = m.data[10] + a;
  dst[11] = m.data[11] + a;
  dst[12] = m.data[12] + a;
  dst[13] = m.data[13] + a;
  dst[14] = m.data[14] + a;
  dst[15] = m.data[15] + a;
}

inline void Matrix4::add(const Matrix4& a, const Matrix4& b, Matrix4& dst) {
  dst[0] = a.data[0] + b.data[0];
  dst[1] = a.data[1] + b.data[1];
  dst[2] = a.data[2] + b.data[2];
  dst[3] = a.data[3] + b.data[3];
  dst[4] = a.data[4] + b.data[4];
  dst[5] = a.data[5] + b.data[5];
  dst[6] = a.data[6] + b.data[6];
  dst[7] = a.data[7] + b.data[7];
  dst[8] = a.data[8] + b.data[8];
  dst[9] = a.data[9] + b.data[9];
  dst[10] = a.data[10] + b.data[10];
  dst[11] = a.data[11] + b.data[11];
  dst[12] = a.data[12] + b.data[12];
  dst[13] = a.data[13] + b.data[13];
  dst[14] = a.data[14] + b.data[14];
  dst[15] = a.data[15] + b.data[15];
}

inline void Matrix4::subtract(const Matrix4& m, float a, Matrix4& dst) {
  dst[0] = m.data[0] - a;
  dst[1] = m.data[1] - a;
  dst[2] = m.data[2] - a;
  dst[3] = m.data[3] - a;
  dst[4] = m.data[4] - a;
  dst[5] = m.data[5] - a;
  dst[6] = m.data[6] - a;
  dst[7] = m.data[7] - a;
  dst[8] = m.data[8] - a;
  dst[9] = m.data[9] - a;
  dst[10] = m.data[10] - a;
  dst[11] = m.data[11] - a;
  dst[12] = m.data[12] - a;
  dst[13] = m.data[13] - a;
  dst[14] = m.data[14] - a;
  dst[15] = m.data[15] - a;
}

inline void Matrix4::subtract(const Matrix4& a, const Matrix4& b, Matrix4& dst) {
  dst[0] = a.data[0] - b.data[0];
  dst[1] = a.data[1] - b.data[1];
  dst[2] = a.data[2] - b.data[2];
  dst[3] = a.data[3] - b.data[3];
  dst[4] = a.data[4] - b.data[4];
  dst[5] = a.data[5] - b.data[5];
  dst[6] = a.data[6] - b.data[6];
  dst[7] = a.data[7] - b.data[7];
  dst[8] = a.data[8] - b.data[8];
  dst[9] = a.data[9] - b.data[9];
  dst[10] = a.data[10] - b.data[10];
  dst[11] = a.data[11] - b.data[11];
  dst[12] = a.data[12] - b.data[12];
  dst[13] = a.data[13] - b.data[13];
  dst[14] = a.data[14] - b.data[14];
  dst[15] = a.data[15] - b.data[15];
}

inline void Matrix4::multiply(const Matrix4& m, float a, Matrix4& dst) {
  dst[0] = m.data[0] * a;
  dst[1] = m.data[1] * a;
  dst[2] = m.data[2] * a;
  dst[3] = m.data[3] * a;
  dst[4] = m.data[4] * a;
  dst[5] = m.data[5] * a;
  dst[6] = m.data[6] * a;
  dst[7] = m.data[7] * a;
  dst[8] = m.data[8] * a;
  dst[9] = m.data[9] * a;
  dst[10] = m.data[10] * a;
  dst[11] = m.data[11] * a;
  dst[12] = m.data[12] * a;
  dst[13] = m.data[13] * a;
  dst[14] = m.data[14] * a;
  dst[15] = m.data[15] * a;
}

inline void Matrix4::multiply(const Matrix4& a, const Matrix4& b, Matrix4& dst) {
  dst[0] = a[0] * b[0] + a[4] * b[1] + a[8] * b[2] + a[12] * b[3];
  dst[1] = a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13] * b[3];
  dst[2] = a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14] * b[3];
  dst[3] = a[3] * b[0] + a[7] * b[1] + a[11] * b[2] + a[15] * b[3];

  dst[4] = a[0] * b[4] + a[4] * b[5] + a[8] * b[6] + a[12] * b[7];
  dst[5] = a[1] * b[4] + a[5] * b[5] + a[9] * b[6] + a[13] * b[7];
  dst[6] = a[2] * b[4] + a[6] * b[5] + a[10] * b[6] + a[14] * b[7];
  dst[7] = a[3] * b[4] + a[7] * b[5] + a[11] * b[6] + a[15] * b[7];

  dst[8] = a[0] * b[8] + a[4] * b[9] + a[8] * b[10] + a[12] * b[11];
  dst[9] = a[1] * b[8] + a[5] * b[9] + a[9] * b[10] + a[13] * b[11];
  dst[10] = a[2] * b[8] + a[6] * b[9] + a[10] * b[10] + a[14] * b[11];
  dst[11] = a[3] * b[8] + a[7] * b[9] + a[11] * b[10] + a[15] * b[11];

  dst[12] = a[0] * b[12] + a[4] * b[13] + a[8] * b[14] + a[12] * b[15];
  dst[13] = a[1] * b[12] + a[5] * b[13] + a[9] * b[14] + a[13] * b[15];
  dst[14] = a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15];
  dst[15] = a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15];
}

// Transformations
inline void Matrix4::translate(const Matrix4& m, const Vector3& translation, Matrix4& dst) {
  translate(m, translation.x, translation.y, translation.z, dst);
}

inline void Matrix4::translate(const Matrix4& m, float x, float y, float z, Matrix4& dst) {
  Matrix4 t;
  makeTranslation(x, y, z, t);
  multiply(m, t, dst);
}

inline void Matrix4::scale(const Matrix4& m, float a, Matrix4& dst) {
  Matrix4::scale(m, a, a, a, dst);
}

inline void Matrix4::scale(const Matrix4& m, const Vector3& scale, Matrix4& dst) {
  Matrix4::scale(m, scale.x, scale.y, scale.z, dst);
}

inline void Matrix4::scale(const Matrix4& m, float x, float y, float z, Matrix4& dst) {
  Matrix4 s;
  makeScale(x, y, z, s);
  multiply(m, s, dst);
}

inline void Matrix4::rotate(const Matrix4& m, const Quaternion& rotation, Matrix4& dst) {
  Matrix4 r;
  makeRotation(rotation, r);
  multiply(m, r, dst);
}

inline void Matrix4::rotateAxis(const Matrix4& m, const Vector3& axis, float angle, Matrix4& dst) {
  Matrix4 r;
  makeAxisRotation(axis, angle, r);
  multiply(m, r, dst);
}

inline void Matrix4::rotateAroundX(const Matrix4& m, float angle, Matrix4& dst) {
  Matrix4 r;
  makeRotationAroundX(angle, r);
  multiply(m, r, dst);
}

inline void Matrix4::rotateAroundY(const Matrix4& m, float angle, Matrix4& dst) {
  Matrix4 r;
  makeRotationAroundY(angle, r);
  multiply(m, r, dst);
}

inline void Matrix4::rotateAroundZ(const Matrix4& m, float angle, Matrix4& dst) {
  Matrix4 r;
  makeRotationAroundZ(angle, r);
  multiply(m, r, dst);
}

inline void Matrix4::transformPoint(const Matrix4& m, const Vector3& point, Vector3& dst) {
  transformVector(m, Vector4{point, 1.0f}, dst);
}

inline void Matrix4::transformVector(const Matrix4& m, const Vector3& v, Vector3& dst) {
  transformVector(m, {v, 0.0f}, dst);
}

inline void Matrix4::transformVector(const Matrix4& m, const Vector4& v, Vector3& dst) {
  dst.set(
    v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12],
    v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13],
    v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14]
  );
}

inline void Matrix4::transformVector(const Matrix4& m, const Vector4& v, Vector4& dst) {
  dst.set(
    v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3] * m[12],
    v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3] * m[13],
    v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14],
    v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3] * m[15]
  );
}

// Operators
inline Matrix4 Matrix4::operator+(const Matrix4& m) const {
  Matrix4 result;
  add(*this, m, result);
  return result;
}

inline Matrix4 Matrix4::operator-(const Matrix4& m) const {
  Matrix4 result;
  subtract(*this, m, result);
  return result;
}

inline Matrix4& Matrix4::operator+=(const Matrix4& m) {
  add(*this, m, *this);
  return *this;
}

inline Matrix4& Matrix4::operator-=(const Matrix4& m) {
  subtract(*this, m, *this);
  return *this;
}

inline Matrix4 Matrix4::operator-() const {
  Matrix4 result;
  this->negate(result);
  return result;
}

inline Matrix4 Matrix4::operator*(const Matrix4& m) const {
  Matrix4 result;
  multiply(*this, m, result);
  return result;
}

inline Matrix4& Matrix4::operator*=(const Matrix4& m) {
  multiply(*this, m, *this);
}

inline Vector3& operator*=(Vector3& v, const Matrix4& m) {
  Matrix4::transformVector(m, v, v);
  return v;
}

inline Vector3 operator*(const Matrix4& m, const Vector3& v) {
  Vector3 result;
  Matrix4::transformVector(m, v, result);
  return result;
}

inline Vector4& operator*=(Vector4& v, const Matrix4& m) {
  Matrix4::transformVector(m, v, v);
  return v;
}

inline Vector4 operator*(const Matrix4& m, const Vector4& v) {
  Vector4 result;
  Matrix4::transformVector(m, v, result);
  return result;
}

// Singletons
const Matrix4& Matrix4::identity() {
  static Matrix4 value{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  };
  return value;
}

const Matrix4& Matrix4::zero() {
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
