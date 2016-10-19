#include "matrix4.h"
#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"

namespace bellum {

// Transformations
void Matrix4::translate(const Matrix4& m, const Vector3& translation, Matrix4& dst) {
  translate(m, translation.x, translation.y, translation.z, dst);
}

void Matrix4::translate(const Matrix4& m, float x, float y, float z, Matrix4& dst) {
  Matrix4 t;
  makeTranslation(x, y, z, t);
  multiply(m, t, dst);
}

void Matrix4::scale(const Matrix4& m, float a, Matrix4& dst) {
  scale(m, a, a, a, dst);
}

void Matrix4::scale(const Matrix4& m, const Vector3& scale, Matrix4& dst) {
  scale(m, scale.x, scale.y, scale.z, dst);
}

void Matrix4::scale(const Matrix4& m, float x, float y, float z, Matrix4& dst) {
  Matrix4 s;
  makeScale(x, y, z, s);
  multiply(m, s, dst);
}

void Matrix4::rotate(const Matrix4& m, const Quaternion& rotation, Matrix4& dst) {
  Matrix4 r;
  makeRotation(rotation, r);
  multiply(m, r, dst);
}

void Matrix4::rotateAxis(const Matrix4& m, const Vector3& axis, float angle, Matrix4& dst) {
  Matrix4 r;
  makeAxisRotation(axis, angle, r);
  multiply(m, r, dst);
}

void Matrix4::rotateAroundX(const Matrix4& m, float angle, Matrix4& dst) {
  Matrix4 r;
  makeRotationAroundX(angle, r);
  multiply(m, r, dst);
}

void Matrix4::rotateAroundY(const Matrix4& m, float angle, Matrix4& dst) {
  Matrix4 r;
  makeRotationAroundY(angle, r);
  multiply(m, r, dst);
}

void Matrix4::rotateAroundZ(const Matrix4& m, float angle, Matrix4& dst) {
  Matrix4 r;
  makeRotationAroundZ(angle, r);
  multiply(m, r, dst);
}

void Matrix4::transformPoint(const Matrix4& m, const Vector3& point, Vector3& dst) {
  transformVector(m, Vector4{point, 1.0f}, dst);
}

void Matrix4::transformVector(const Matrix4& m, const Vector3& v, Vector3& dst) {
  transformVector(m, {v, 0.0f}, dst);
}

void Matrix4::transformVector(const Matrix4& m, const Vector4& v, Vector3& dst) {
  dst.set(
    v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12],
    v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13],
    v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14]
  );
}

void Matrix4::transformVector(const Matrix4& m, const Vector4& v, Vector4& dst) {

}

// Factory methods
void Matrix4::makeIdentity(Matrix4& dst) {
  std::memset(&dst, 0, 16);
  dst.set(0, 0, 1.0f);
  dst.set(1, 1, 1.0f);
  dst.set(2, 2, 1.0f);
  dst.set(3, 3, 1.0f);
}

void Matrix4::makeLookAt(const Vector3& position, const Vector3& target, const Vector3& up,
                         Matrix4& dst) {

}

void Matrix4::makeOrthographic(float left, float right,
                               float bottom, float top,
                               float near, float far,
                               Matrix4& dst) {
}

void Matrix4::makePerspective(float fov, float aspectRatio, float near, float far, Matrix4& dst) {
}

void Matrix4::makeBillboard(const Vector3& position, const Vector3& cameraPosition,
                            const Vector3& cameraUp, Matrix4& dst) {
}

void Matrix4::makeReflection(const Plane& plane, Matrix4& dst) {
}

void Matrix4::makeTranslation(const Vector3& translation, Matrix4& dst) {
  makeTranslation(translation.x, translation.y, translation.z, dst);
}

void Matrix4::makeTranslation(float x, float y, float z, Matrix4& dst) {
  std::memset(&dst, 0, 16);
  dst.set(0, 0, 1.0f);
  dst.set(0, 3, x);
  dst.set(1, 1, 1.0f);
  dst.set(1, 3, y);
  dst.set(2, 2, 1.0f);
  dst.set(2, 3, z);
  dst.set(3, 3, 1.0f);
}

void Matrix4::makeScale(const Vector3& scale, Matrix4& dst) {
  makeScale(scale.x, scale.y, scale.z, dst);
}

void Matrix4::makeScale(float x, float y, float z, Matrix4& dst) {
  std::memset(&dst, 0, 16);
  dst.set(0, x);
  dst.set(5, y);
  dst.set(10, z);
  dst.set(15, 1.0f);
}

void Matrix4::makeRotation(const Vector3& forward, const Vector3& up, const Vector3& right,
                           Matrix4& dst) {
  std::memset(&dst, 0, 16);
  dst.set(0, 0, right.x);
  dst.set(0, 1, right.y);
  dst.set(0, 2, right.z);
  dst.set(1, 0, up.x);
  dst.set(1, 1, up.y);
  dst.set(1, 2, up.z);
  dst.set(2, 0, forward.x);
  dst.set(2, 1, forward.y);
  dst.set(2, 2, forward.z);
  dst.set(3, 3, 1.0f);
}

void Matrix4::makeRotation(const Vector3& forward, const Vector3& up, Matrix4& dst) {
  Vector3 f;
  forward.normalize(f);
  Vector3 r;
  up.normalize(r);
  Vector3::cross(r, f, r);
  Vector3 u;
  Vector3::cross(f, r, u);

  makeRotation(f, u, r, dst);
}

void Matrix4::makeRotation(const Quaternion& q, Matrix4& dst) {
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

  dst[0] = 1.0f - yy2 - zz2;
  dst[1] = xy2 + wz2;
  dst[2] = xz2 - wy2;
  dst[3] = 0.0f;
  dst[4] = xy2 - wz2;
  dst[5] = 1.0f - xx2 - zz2;
  dst[6] = yz2 + wx2;
  dst[7] = 0.0f;
  dst[8] = xz2 + wy2;
  dst[9] = yz2 - wx2;
  dst[10] = 1.0f - xx2 - yy2;
  dst[11] = 0.0f;
  dst[12] = 0.0f;
  dst[13] = 0.0f;
  dst[14] = 0.0f;
  dst[15] = 1.0f;
}

void Matrix4::makeAxisRotation(const Vector3& axis, float angle, Matrix4& dst) {

}

void Matrix4::makeEulerRotation(const Vector3& eulerAngles, Matrix4& dst) {

}

void Matrix4::makeEulerRotation(float x, float y, float z, Matrix4& dst) {

}

void Matrix4::makeRotationAroundX(float angle, Matrix4& dst) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  std::memset(&dst, 0, 16);
  dst.set(0, 0, 1.0f);
  dst.set(1, 1, cos);
  dst.set(1, 2, sin);
  dst.set(2, 1, sin);
  dst.set(2, 2, cos);
  dst.set(3, 3, 1.0f);
}

void Matrix4::makeRotationAroundY(float angle, Matrix4& dst) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  std::memset(&dst, 0, 16);
  dst.set(0, 0, cos);
  dst.set(0, 2, -sin);
  dst.set(1, 1, 1.0f);
  dst.set(2, 0, sin);
  dst.set(2, 2, cos);
  dst.set(3, 3, 1.0f);
}

void Matrix4::makeRotationAroundZ(float angle, Matrix4& dst) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  std::memset(&dst, 0, 16);
  dst.set(0, 0, cos);
  dst.set(0, 1, sin);
  dst.set(1, 0, sin);
  dst.set(1, 1, cos);
  dst.set(2, 2, 1.0f);
  dst.set(3, 3, 1.0f);
}

}
