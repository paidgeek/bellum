#include "quaternion.h"
#include "matrix4.h"

namespace bellum {

// Setters
void Quaternion::set(const Matrix4& m) {
  float m11 = m.get(0, 0);
  float m22 = m.get(1, 1);
  float m33 = m.get(2, 2);
  float trace = m11 + m22 + m33;

  if (trace > 0.0f) {
    float s = 0.5f / Math::sqrt(trace + 1.0f);
    w = 0.25f / s;
    x = (m.get(1, 2) - m.get(2, 1)) * s;
    y = (m.get(2, 0) - m.get(0, 2)) * s;
    z = (m.get(0, 1) - m.get(1, 0)) * s;
  } else {
    if (m11 > m22 && m11 > m33) {
      float s = 2.0f * Math::sqrt(1.0f + m11 - m22 - m33);
      w = (m.get(1, 2) - m.get(2, 1)) / s;
      x = 0.25f * s;
      y = (m.get(1, 0) + m.get(0, 1)) / s;
      z = (m.get(2, 0) + m.get(0, 2)) / s;
    } else if (m22 > m33) {
      float s = 2.0f * Math::sqrt(1.0f + m22 - m11 - m33);
      w = (m.get(2, 0) - m.get(0, 2)) / s;
      x = (m.get(1, 0) + m.get(0, 1)) / s;
      y = 0.25f * s;
      z = (m.get(2, 1) + m.get(1, 2)) / s;
    } else {
      float s = 2.0f * Math::sqrt(1.0f + m33 - m11 - m22);
      w = (m.get(0, 1) - m.get(1, 0)) / s;
      x = (m.get(2, 0) + m.get(0, 2)) / s;
      y = (m.get(1, 2) + m.get(2, 1)) / s;
      z = 0.25f * s;
    }
  }

  this->normalize();
}

// Algebra
Vector3 Quaternion::toEulerAngles() const {
  return {
    Math::atan2(2.0f * (w * x + y * z), 1.0f - 2.0f * (x * x + y * y)),
    Math::asin(2.0f * (w * y - z * x)),
    Math::atan2(2.0f * (w * z + x * y), 1.0f - 2.0f * (y * y + z * z))
  };
}

// Utilities
void Quaternion::rotatePoint(const Quaternion& q, const Vector3& point, Vector3& dst) {
  // TODO
}

// Factory methods
void Quaternion::makeIdentity(Quaternion& dst) {
  dst.set(0.0f, 0.0f, 0.0f, 1.0f);
}

void Quaternion::makeEuler(const Vector3& eulerAngles, Quaternion& dst) {
  makeEuler(eulerAngles.x, eulerAngles.y, eulerAngles.z, dst);
}

void Quaternion::makeEuler(float x, float y, float z, Quaternion& dst) {
  x /= 2.0f;
  y /= 2.0f;
  z /= 2.0f;
  float sinx = Math::sin(x);
  float cosx = Math::cos(x);
  float siny = Math::sin(y);
  float cosy = Math::cos(y);
  float sinz = Math::sin(z);
  float cosz = Math::cos(z);

  dst.set(
    siny * cosx * cosz - cosy * sinx * sinz,
    cosy * sinx * cosz + siny * cosx * sinz,
    cosy * cosx * sinz - siny * sinx * cosz,
    cosy * cosx * cosz + siny * sinx * sinz
  );
}

void Quaternion::makeAxisAngle(const Vector3& axis, float angle, Quaternion& dst) {
  float ha = angle / 2.0f;
  float sin = Math::sin(ha);
  Vector3 n;
  axis.normalize(n);

  dst.set(n.x * sin, n.y * sin, n.z * sin, ha);
}

void Quaternion::makeLookAt(const Vector3& direction, const Vector3& up, Quaternion& dst) {
  Vector3 f;
  direction.normalize(f);

  Vector3 r;
  Vector3::cross(f, up, r);
  r.normalize();

  Vector3 u;
  Vector3::cross(r, f, u);

  Matrix4 m;
  Matrix4::makeRotation(f, up, m);
  dst.set(m);
}

}
