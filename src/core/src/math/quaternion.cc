#include "quaternion.h"
#include "vector3.h"
#include "matrix4.h"

namespace bellum {

// Constructors
Quaternion::Quaternion(const Matrix4& m) {
  fromRotationMatrix(m, this);
}

Quaternion::Quaternion(const Vector3& axis, float angle) {
  fromAxisAngle(axis, angle, this);
}

// Setters
void Quaternion::set(const Matrix4& m) {
  fromRotationMatrix(m, this);
}

void Quaternion::set(const Vector3& axis, float angle) {
  fromAxisAngle(axis, angle, this);
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
void Quaternion::rotatePoint(const Vector3& point, Vector3* dst) const {
  rotatePoint(*this, point, dst);
}

void Quaternion::rotatePoint(const Quaternion& q, const Vector3& point, Vector3* dst) {
  Quaternion vecQuat;
  Quaternion resQuat;
  vecQuat.x = point.x;
  vecQuat.y = point.y;
  vecQuat.z = point.z;
  vecQuat.w = 0.0f;

  Quaternion conQuat;
  q.conjugate(&conQuat);

  resQuat = vecQuat * conQuat;
  resQuat = q * resQuat;

  dst->set(resQuat.x, resQuat.y, resQuat.z);
}

Quaternion& Quaternion::lerp(const Quaternion& b, float t) {
  lerp(*this, b, t, this);
  return *this;
}

void Quaternion::lerp(const Quaternion& a, const Quaternion& b, float t, Quaternion* dst) {
  if (t == 0.0f) {
    std::memcpy(dst, &a, sizeof(float) * 4);
    return;
  } else if (t == 1.0f) {
    std::memcpy(dst, &b, sizeof(float) * 4);
    return;
  }

  float t1 = 1.0f - t;

  dst->x = t1 * a.x + t * b.x;
  dst->y = t1 * a.y + t * b.y;
  dst->z = t1 * a.z + t * b.z;
  dst->w = t1 * a.w + t * b.w;
}

Quaternion& Quaternion::slerp(const Quaternion& b, float t) {
  slerp(*this, b, t, this);
  return *this;
}

void Quaternion::slerp(const Quaternion& a, const Quaternion& b, float t, Quaternion* dst) {
  if (t == 0.0f) {
    dst->set(a);
    return;
  } else if (t == 1.0f) {
    dst->set(b);
    return;
  }

  if (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w) {
    dst->set(a);
    return;
  }

  float halfY, alpha, beta;
  float u, f1, f2a, f2b;
  float ratio1, ratio2;
  float halfSecHalfTheta, versHalfTheta;
  float sqNotU, sqU;

  float cosTheta = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;

  alpha = cosTheta >= 0 ? 1.0f : -1.0f;
  halfY = 1.0f + alpha * cosTheta;

  f2b = t - 0.5f;
  u = f2b >= 0 ? f2b : -f2b;
  f2a = u - f2b;
  f2b += u;
  u += u;
  f1 = 1.0f - u;

  halfSecHalfTheta = 1.09f - (0.476537f - 0.0903321f * halfY) * halfY;
  halfSecHalfTheta *= 1.5f - halfY * halfSecHalfTheta * halfSecHalfTheta;
  versHalfTheta = 1.0f - halfY * halfSecHalfTheta;

  sqNotU = f1 * f1;
  ratio2 = 0.0000440917108f * versHalfTheta;
  ratio1 = -0.00158730159f + (sqNotU - 16.0f) * ratio2;
  ratio1 = 0.0333333333f + ratio1 * (sqNotU - 9.0f) * versHalfTheta;
  ratio1 = -0.333333333f + ratio1 * (sqNotU - 4.0f) * versHalfTheta;
  ratio1 = 1.0f + ratio1 * (sqNotU - 1.0f) * versHalfTheta;

  sqU = u * u;
  ratio2 = -0.00158730159f + (sqU - 16.0f) * ratio2;
  ratio2 = 0.0333333333f + ratio2 * (sqU - 9.0f) * versHalfTheta;
  ratio2 = -0.333333333f + ratio2 * (sqU - 4.0f) * versHalfTheta;
  ratio2 = 1.0f + ratio2 * (sqU - 1.0f) * versHalfTheta;

  f1 *= ratio1 * halfSecHalfTheta;
  f2a *= ratio2;
  f2b *= ratio2;
  alpha *= f1 + f2a;
  beta = f1 + f2b;

  float w = alpha * a.w + beta * b.w;
  float x = alpha * a.x + beta * b.x;
  float y = alpha * a.y + beta * b.y;
  float z = alpha * a.z + beta * b.z;

  f1 = 1.5f - 0.5f * (w * w + x * x + y * y + z * z);
  dst->set(x * f1, y * f1, z * f1, w * f1);
}

void Quaternion::fromEuler(const Vector3& eulerAngles, Quaternion* dst) {
  fromEuler(eulerAngles.x, eulerAngles.y, eulerAngles.z, dst);
}

void Quaternion::fromEuler(float x, float y, float z, Quaternion* dst) {
  x /= 2.0f;
  y /= 2.0f;
  z /= 2.0f;
  float sinx = Math::sin(x);
  float cosx = Math::cos(x);
  float siny = Math::sin(y);
  float cosy = Math::cos(y);
  float sinz = Math::sin(z);
  float cosz = Math::cos(z);

  dst->w = cosy * cosx * cosz + siny * sinx * sinz;
  dst->x = siny * cosx * cosz - cosy * sinx * sinz;
  dst->y = cosy * sinx * cosz + siny * cosx * sinz;
  dst->z = cosy * cosx * sinz - siny * sinx * cosz;
}

void Quaternion::fromRotationMatrix(const Matrix4& m, Quaternion* dst) {

}

void Quaternion::fromAxisAngle(const Vector3& axis, float angle, Quaternion* dst) {
  float ha = angle / 2.0f;
  float sinHa = Math::sin(ha);
  Vector3 n;
  axis.normalize(&n);

  dst->set(n.x * sinHa, n.y * sinHa, n.z * sinHa, ha);
}

void Quaternion::fromLookAt(const Vector3& direction, const Vector3& up, Quaternion* dst) {
  Vector3 f;
  direction.normalize(&f);

  Vector3 r;
  Vector3::cross(f, up, &r);
  r.normalize();

  Vector3 u;
  Vector3::cross(r, f, &u);

  Matrix4 m;
  Matrix4::fromRotation(f, up);
  dst->set(m);
}

}
