#include "quaternion.h"
#include "matrix4.h"
#include "vector3.h"

namespace bellum {

Quaternion::Quaternion(const Matrix4& m) {
  set(m);
}

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

Quaternion Quaternion::makeLookRotation(const Vector3& forward, const Vector3& upwards) {
  Vector3 f = forward.normalized();
  Vector3 r = Vector3::cross(f, upwards).normalized();
  Vector3 u = Vector3::cross(r, f);

  Matrix4 m = Matrix4::makeRotation(f, upwards);

  return Quaternion{m};
}

}
