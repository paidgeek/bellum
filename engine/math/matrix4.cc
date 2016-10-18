#include "matrix4.h"
#include "vector3.h"
#include "vector4.h"
#include "plane.h"

namespace bellum {

// Factory methods
void Matrix4::makeIdentity(Matrix4* dst) {
  std::memset(dst, 0, 16);
  dst->set(0, 0, 1.0f);
  dst->set(1, 1, 1.0f);
  dst->set(2, 2, 1.0f);
  dst->set(3, 3, 1.0f);
}

void Matrix4::makeLookAt(const Vector3& position, const Vector3& target, const Vector3& up,
                         Matrix4* dst) {

}

void Matrix4::makeOrthographic(float left, float right,
                               float bottom, float top,
                               float near, float far,
                               Matrix4* dst) {
}

void Matrix4::makePerspective(float fov, float aspectRatio, float near, float far, Matrix4* dst) {
}

void Matrix4::makeBillboard(const Vector3& position, const Vector3& cameraPosition,
                            const Vector3& cameraUp, Matrix4* dst) {
}

void Matrix4::makeReflection(const Plane& plane, Matrix4* dst) {
}

void Matrix4::makeTranslation(const Vector3& translation, Matrix4* dst) {
  makeTranslation(translation.x, translation.y, translation.z, dst);
}

void Matrix4::makeTranslation(float x, float y, float z, Matrix4* dst) {
  std::memset(dst, 0, 16);
  dst->set(0, 0, 1.0f);
  dst->set(0, 3, x);
  dst->set(1, 1, 1.0f);
  dst->set(1, 3, y);
  dst->set(2, 2, 1.0f);
  dst->set(2, 3, z);
  dst->set(3, 3, 1.0f);
}

void Matrix4::makeScale(const Vector3& scale, Matrix4* dst) {
  makeScale(scale.x, scale.y, scale.z, dst);
}

void Matrix4::makeScale(float x, float y, float z, Matrix4* dst) {
  std::memset(dst, 0, 16);
  dst->set(0, x);
  dst->set(5, y);
  dst->set(10, z);
  dst->set(15, 1.0f);
}

void Matrix4::makeRotation(const Vector3& forward, const Vector3& up, const Vector3& right,
                           Matrix4* dst) {
  std::memset(dst, 0, 16);
  dst->set(0, 0, right.x);
  dst->set(0, 1, right.y);
  dst->set(0, 2, right.z);
  dst->set(1, 0, up.x);
  dst->set(1, 1, up.y);
  dst->set(1, 2, up.z);
  dst->set(2, 0, forward.x);
  dst->set(2, 1, forward.y);
  dst->set(2, 2, forward.z);
  dst->set(3, 3, 1.0f);
}

void Matrix4::makeRotation(const Vector3& forward, const Vector3& up, Matrix4* dst) {
  Vector3 f;
  forward.normalize(&f);
  Vector3 r;
  up.normalize(&r);
  r.cross(f);
  Vector3 u;
  Vector3::cross(f, r, &u);

  makeRotation(f, u, r, dst);
}

void Matrix4::makeAxisRotation(const Vector3& axis, float angle, Matrix4* dst) {

}

void Matrix4::makeEulerRotation(const Vector3& eulerAngles, Matrix4* dst) {

}

void Matrix4::makeEulerRotation(float x, float y, float z, Matrix4* dst) {

}

void Matrix4::makeRotationAroundX(float angle, Matrix4* dst) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  std::memset(dst, 0, 16);
  dst->set(0, 0, 1.0f);
  dst->set(1, 1, cos);
  dst->set(1, 2, sin);
  dst->set(2, 1, sin);
  dst->set(2, 2, cos);
  dst->set(3, 3, 1.0f);
}

void Matrix4::makeRotationAroundY(float angle, Matrix4* dst) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  std::memset(dst, 0, 16);
  dst->set(0, 0, cos);
  dst->set(0, 2, -sin);
  dst->set(1, 1, 1.0f);
  dst->set(2, 0, sin);
  dst->set(2, 2, cos);
  dst->set(3, 3, 1.0f);
}

void Matrix4::makeRotationAroundZ(float angle, Matrix4* dst) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  std::memset(dst, 0, 16);
  dst->set(0, 0, cos);
  dst->set(0, 1, sin);
  dst->set(1, 0, sin);
  dst->set(1, 1, cos);
  dst->set(2, 2, 1.0f);
  dst->set(3, 3, 1.0f);
}

}
