#ifndef BELLUM_MATRIX4_H
#define BELLUM_MATRIX4_H

#include "math.h"
#include <ostream>
#include <cstring>
#include <array>

namespace bellum {

struct Plane;
struct Vector3;
struct Vector4;
struct Matrix3;
struct Quaternion;

struct Matrix4 {
  float data[16];

  Matrix4();
  Matrix4(const float* data);
  Matrix4(const std::array<float, 16>& data);
  Matrix4(float m11, float m12, float m13, float m14,
          float m21, float m22, float m23, float m24,
          float m31, float m32, float m33, float m34,
          float m41, float m42, float m43, float m44);
  Matrix4(std::array<std::array<float, 4>, 4> data);

  Matrix4(const Matrix4& m);
  Matrix4& operator=(const Matrix4& m);

  void set(const Matrix4& m);
  void set(const float* data);
  void set(const std::array<float, 16>& data);
  void set(float m11, float m12, float m13, float m14,
           float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34,
           float m41, float m42, float m43, float m44);
  void set(std::array<std::array<float, 4>, 4> data);

  float& operator[](int32 i, int32 j);

  float determinant() const;
  Matrix4& inverse();
  void inverse(Matrix4* dst) const;
  Matrix4& negate();
  void negate(Matrix4* dst) const;
  Matrix4& transpose();
  void transpose(Matrix4* dst) const;

  static void add(const Matrix4& m, float a, Matrix4* dst);
  static void add(const Matrix4& a, const Matrix4& b, Matrix4* dst);
  static void subtract(const Matrix4& m, float a, Matrix4* dst);
  static void subtract(const Matrix4& a, const Matrix4& b, Matrix4* dst);
  static void multiply(const Matrix4& m, float a, Matrix4* dst);
  static void multiply(const Matrix4& a, const Matrix4& b, Matrix4* dst);
  static void translate(const Matrix4& m, const Vector3& translation, Matrix4* dst);
  static void translate(const Matrix4& m, float x, float y, float z, Matrix4* dst);
  static void scale(const Matrix4& m, float a, Matrix4* dst);
  static void scale(const Matrix4& m, const Vector3& scale, Matrix4* dst);
  static void scale(const Matrix4& m, float x, float y, float z, Matrix4* dst);
  static void rotate(const Matrix4& m, const Quaternion& rotation, Matrix4* dst);
  static void rotate(const Matrix4& m, float angle, Matrix4* dst);
  static void rotateAroundX(const Matrix4& m, float angle, Matrix4* dst);
  static void rotateAroundY(const Matrix4& m, float angle, Matrix4* dst);
  static void rotateAroundZ(const Matrix4& m, float angle, Matrix4* dst);

  static void transformPoint(const Matrix4& m, const Vector3& point, Vector3* dst);
  static void transformVector(const Matrix4& m, const Vector3& vector, Vector3* dst);
  static void transformVector(const Matrix4& m, const Vector4& vector, Vector4* dst);

  inline Matrix4 operator+(const Matrix4& m) const;
  inline Matrix4 operator-(const Matrix4& m) const;
  inline Matrix4& operator+=(const Matrix4& m);
  inline Matrix4& operator-=(const Matrix4& m);
  inline Matrix4 operator-() const;
  inline Matrix4 operator*(const Matrix4& m) const;
  inline Matrix4& operator*=(const Matrix4& m);

  bool decompose(Vector3* translation, Vector3* scale, Quaternion* rotation) const;
  void getScale(Vector3* dst) const;
  bool getRotation(Quaternion* dst) const;
  void getTranslation(Vector3* dst) const;
  void getUpVector(Vector3* dst) const;
  void getDownVector(Vector3* dst) const;
  void getLeftVector(Vector3* dst) const;
  void getRightVector(Vector3* dst) const;
  void getForwardVector(Vector3* dst) const;
  void getBackVector(Vector3* dst) const;

  static void makeIdentity(Matrix4* dst);
  static void makeLookAt(const Vector3& position, const Vector3& target, const Vector3& up, Matrix4* dst);
  static void makeOrthographic(float left, float right, float bottom, float top, float near, float far, Matrix4* dst);
  static void makePerspective(float fov, float aspectRatio, float near, float far, Matrix4* dst);
  static void makeBillboard(const Vector3& position, const Vector3& cameraPosition, const Vector3& cameraUp, Matrix4* dst);
  static void makeReflection(const Plane& plane, Matrix4* dst);
  static void makeTranslation(const Vector3& translation, Matrix4* dst);
  static void makeTranslation(float x, float y, float z, Matrix4* dst);
  static void makeScale(const Vector3& scale, Matrix4* dst);
  static void makeScale(float x, float y, float z, Matrix4* dst);
  static void makeRotation(const Vector3& forward, const Vector3& up, const Vector3& right, Matrix4* dst);
  static void makeRotation(const Vector3& forward, const Vector3& up, Matrix4* dst);
  static void makeAxisRotation(const Vector3& axis, float angle, Matrix4* dst);
  static void makeEulerRotation(const Vector3& eulerAngles, Matrix4* dst);
  static void makeEulerRotation(float x, float y, float z, Matrix4* dst);
  static void makeRotationAroundX(float angle, Matrix4* dst);
  static void makeRotationAroundY(float angle, Matrix4* dst);
  static void makeRotationAroundZ(float angle, Matrix4* dst);

  static const Matrix4& identity();
  static const Matrix4& zero();

  friend std::ostream& operator<<(std::ostream& os, const Matrix4& m);
};

inline Vector3& operator*=(Vector3& v, const Matrix4& m);
inline Vector3 operator*(const Matrix4& m, const Vector3& v);
inline Vector4& operator *=(Vector4& v, const Matrix4& m);
inline Vector4 operator*(const Matrix4& m, const Vector4& v);

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

// Setters
void Matrix4::set(const Matrix4& m) {
  std::memcpy(this->data, m.data, 16);
}

void Matrix4::set(const float* data) {
  std::memcpy(this->data, data, 16);
}

void Matrix4::set(const std::array<float, 16>& data) {
  std::memcpy(this->data, data.data(), 16);
}

void Matrix4::set(float m11, float m12, float m13, float m14,
         float m21, float m22, float m23, float m24,
         float m31, float m32, float m33, float m34,
         float m41, float m42, float m43, float m44) {
  data[0]  = m11;
  data[1]  = m21;
  data[2]  = m31;
  data[3]  = m41;
  data[4]  = m12;
  data[5]  = m22;
  data[6]  = m32;
  data[7]  = m42;
  data[8]  = m13;
  data[9]  = m23;
  data[10] = m33;
  data[11] = m43;
  data[12] = m14;
  data[13] = m24;
  data[14] = m34;
  data[15] = m44;
}

void Matrix4::set(std::array<std::array<float, 4>, 4> data) {
  std::memcpy(this->data, data.data(), 16);
}

inline std::ostream& operator<<(std::ostream& os, const Matrix4& m) {
  os << "Matrix4(" << '\n';
  os << " " << m[0];
  os << ')';
  return os;
}

}

#endif
