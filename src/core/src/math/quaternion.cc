#include "quaternion.h"
#include "vector3.h"
#include "matrix4.h"

namespace bellum {

Quaternion::Quaternion(const Matrix4& m) {

}

Vector3 Quaternion::eulerAngles() const {
  return {
    Math::atan2(2.0f * (w * x + y * z), 1.0f - 2.0f * (x * x + y * y)),
    Math::asin(2.0f * (w * y - z * x)),
    Math::atan2(2.0f * (w * z + x * y), 1.0f - 2.0f * (y * y + z * z))
  };
}

Quaternion operator*(const Quaternion& q, const Vector3& v) const {
  return {
    -q.x * v.x - q.y * v.y - q.z * v.z,
    q.w * v.x + q.y * v.z - q.z * v.y,
    q.w * v.y + q.z * v.x - q.x * v.z,
    q.w * v.z + q.x * v.y - q.y * v.x
  };
}

Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, float t) {

}

Quaternion Quaternion::euler(const Vector3& euler) {

}

Quaternion Quaternion::euler(float x, float y, float z) {

}

Quaternion Quaternion::lookAt(const Vector3& direction, const Vector3& up) {

}

Quaternion Quaternion::axisAngle(const Vector3& axis, float angle) {

}

}
