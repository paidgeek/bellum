#include "matrix4.h"

namespace bellum {

Matrix4& Matrix4::loadIdentity() {
}

Matrix4& Matrix4::loadTranslation(const Vector3& v) {

}

Matrix4& Matrix4::loadTranslation(float x, float y, float z);
Matrix4& Matrix4::loadRotationAroundX(float angle);
Matrix4& Matrix4::loadRotationAroundY(float angle);
Matrix4& Matrix4::loadRotationAroundZ(float angle);
Matrix4& Matrix4::loadRotation(const Vector3& euler);
Matrix4& Matrix4::loadRotation(float x, float y, float z);
Matrix4& Matrix4::loadRotation(const Vector3& forward, const Vector3& up, const Vector3& right);
Matrix4& Matrix4::loadRotation(const Vector3& forward, const Vector3& up);
Matrix4& Matrix4::loadScale(const Vector3& scale);
Matrix4& Matrix4::loadScale(float x, float y, float z);
Matrix4& Matrix4::loadOrthographic(float left, float right, float bottom, float top, float near, float far);
Matrix4& Matrix4::loadPerspective(float fov, float aspectRatio, float near, float far);

}
