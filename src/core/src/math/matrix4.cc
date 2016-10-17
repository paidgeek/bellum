#include "core/math/matrix4.h"

namespace bellum {

// Factory methods
void Matrix4::makeIdentity(Matrix4* dst) {

}

void Matrix4::makeLookAt(const Vector3& position, const Vector3& target, const Vector3& up,
                         Matrix4* dst) {

}

void
Matrix4::makeOrthographic(float left, float right, float bottom, float top, float near, float far,
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

}

void Matrix4::makeTranslation(float x, float y, float z, Matrix4* dst) {

}

void Matrix4::makeScale(const Vector3& scale, Matrix4* dst) {

}

void Matrix4::makeScale(float x, float y, float z, Matrix4* dst) {

}

void Matrix4::makeRotation(const Vector3& forward, const Vector3& up, const Vector3& right,
                           Matrix4* dst) {

}

void Matrix4::makeRotation(const Vector3& forward, const Vector3& up, Matrix4* dst) {

}

void Matrix4::makeAxisRotation(const Vector3& axis, float angle, Matrix4* dst) {

}

void Matrix4::makeEulerRotation(const Vector3& eulerAngles, Matrix4* dst) {

}

void Matrix4::makeEulerRotation(float x, float y, float z, Matrix4* dst) {

}

void Matrix4::makeRotationAroundX(float angle, Matrix4* dst) {

}

void Matrix4::makeRotationAroundY(float angle, Matrix4* dst) {

}

void Matrix4::makeRotationAroundZ(float angle, Matrix4* dst) {

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

}
