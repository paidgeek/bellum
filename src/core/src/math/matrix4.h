#ifndef BELLUM_MATRIX4_H
#define BELLUM_MATRIX4_H

#include <cstring>
#include <array>

namespace bellum {

struct Vector3;
struct Matrix3;

struct Matrix4 {
  float data[4][4];

  Matrix4();
  Matrix4(const Matrix4& m);
  Matrix4(std::array<std::array<float, 4>, 4> data);
  Matrix4& operator=(const Matrix4& m);

  float* operator[](int32_t i);

  Matrix4& transpose();
  Matrix4 transposed() const;
  Matrix4& inverse();
  Matrix4 inversed() const;

  Matrix4& loadIdentity();
  Matrix4& loadTranslation(const Vector3& v);
  Matrix4& loadTranslation(float x, float y, float z);
  Matrix4& loadRotationAroundX(float angle);
  Matrix4& loadRotationAroundY(float angle);
  Matrix4& loadRotationAroundZ(float angle);
  Matrix4& loadRotation(const Vector3& euler);
  Matrix4& loadRotation(float x, float y, float z);
  Matrix4& loadRotation(const Vector3& forward, const Vector3& up, const Vector3& right);
  Matrix4& loadRotation(const Vector3& forward, const Vector3& up);
  Matrix4& loadScale(const Vector3& scale);
  Matrix4& loadScale(float x, float y, float z);
  Matrix4& loadOrthographic(float left, float right, float bottom, float top, float near, float far);
  Matrix4& loadPerspective(float fov, float aspectRatio, float near, float far);

  static Matrix4 identity();
};

Matrix4::Matrix4() {
  std::memset(this->data, 0, 16);
}

Matrix4::Matrix4(const Matrix4& m) {
  std::memcpy(this->data, m.data, 16);
}

Matrix4::Matrix4(std::array<std::array<float, 4>, 4> data) {

}

Matrix4& Matrix4::operator=(const Matrix4& m) {
  std::memcpy(this->data, m.data, 16);
}

float* Matrix4::operator[](int32_t i) {
  return this->data[i];
}

Matrix4& Matrix4::transpose() {
  return {};
}

Matrix4 Matrix4::transposed() const {

}

Matrix4& Matrix4::inverse() {

}

Matrix4 Matrix4::inversed() const {

}

inline Matrix4 Matrix4::identity() {
  return Matrix4().loadIdentity();
}

}

#endif
