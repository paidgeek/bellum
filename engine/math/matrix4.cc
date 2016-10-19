#include "matrix4.h"

namespace bellum {

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
  Vector3 upNorm;
  up.normalize(upNorm);

  Vector3 zaxis;
  Vector3::subtract(position, target, zaxis);
  zaxis.normalize();

  Vector3 xaxis;
  Vector3::cross(up, zaxis, xaxis);
  xaxis.normalize();

  Vector3 yaxis;
  Vector3::cross(zaxis, xaxis, yaxis);
  yaxis.normalize();

  dst[0] = xaxis.x;
  dst[1] = yaxis.x;
  dst[2] = zaxis.x;
  dst[3] = 0.0f;

  dst[4] = xaxis.y;
  dst[5] = yaxis.y;
  dst[6] = zaxis.y;
  dst[7] = 0.0f;

  dst[8] = xaxis.z;
  dst[9] = yaxis.z;
  dst[10] = zaxis.z;
  dst[11] = 0.0f;

  dst[12] = -Vector3::dot(xaxis, position);
  dst[13] = -Vector3::dot(yaxis, position);
  dst[14] = -Vector3::dot(zaxis, position);
  dst[15] = 1.0f;
}

void Matrix4::makeOrthographic(float left, float right,
                               float bottom, float top,
                               float near, float far,
                               Matrix4& dst) {
  std::memset(dst.data, 0, 16);
  dst[0] = 2 / (right - left);
  dst[5] = 2 / (top - bottom);
  dst[12] = (left + right) / (left - right);
  dst[10] = 1 / (near - far);
  dst[13] = (top + bottom) / (bottom - top);
  dst[14] = near / (near - far);
  dst[15] = 1;
}

void Matrix4::makePerspective(float fov, float aspectRatio, float near, float far, Matrix4& dst) {
  float f = 1.0f / (far - near);
  float theta = Math::kDegToRad * fov / 2.0f;

  float d = Math::tan(theta);
  float m = 1.0f / d;

  std::memset(dst.data, 0, 16);
  dst.data[0] = (1.0f / aspectRatio) * m;
  dst.data[5] = m;
  dst.data[10] = f * (-far - near);
  dst.data[11] = -1.0f;
  dst.data[14] = -2.0f * far * near * f;
}

void Matrix4::makeBillboard(const Vector3& position, const Vector3& cameraPosition,
                            const Vector3& cameraUp, const Vector3& cameraForward, Matrix4& dst) {
  dst.set(identity());
  dst[3] = position.x;
  dst[7] = position.y;
  dst[11] = position.z;

  Matrix4 lookAt;
  makeLookAt(position, cameraPosition, cameraUp, lookAt);
  dst[0] = lookAt[0];
  dst[1] = lookAt[4];
  dst[2] = lookAt[8];
  dst[4] = lookAt[1];
  dst[5] = lookAt[5];
  dst[6] = lookAt[9];
  dst[8] = lookAt[2];
  dst[9] = lookAt[6];
  dst[10] = lookAt[10];
}

void Matrix4::makeReflection(const Plane& plane, Matrix4& dst) {
  Vector3 n(plane.normal);
  float k = -2.0f * plane.distance;

  dst.set(identity());

  dst[0] -= 2.0f * n.x * n.x;
  dst[5] -= 2.0f * n.y * n.y;
  dst[10] -= 2.0f * n.z * n.z;
  dst[1] = dst[4] = -2.0f * n.x * n.y;
  dst[2] = dst[8] = -2.0f * n.x * n.z;
  dst[6] = dst[9] = -2.0f * n.y * n.z;
  dst[3] = k * n.x;
  dst[7] = k * n.y;
  dst[11] = k * n.z;
}

void Matrix4::makeTranslation(const Vector3& translation, Matrix4& dst) {
  makeTranslation(translation.x, translation.y, translation.z, dst);
}

void Matrix4::makeTranslation(float x, float y, float z, Matrix4& dst) {
  dst.set(identity());
  dst[12] = x;
  dst[13] = y;
  dst[14] = z;
}

void Matrix4::makeScale(const Vector3& scale, Matrix4& dst) {
  makeScale(scale.x, scale.y, scale.z, dst);
}

void Matrix4::makeScale(float x, float y, float z, Matrix4& dst) {
  dst.set(identity());
  dst[0] = x;
  dst[5] = y;
  dst[10] = z;
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
  float x = axis.x;
  float y = axis.y;
  float z = axis.z;

  float n = x * x + y * y + z * z;

  if (n != 1.0f) {
    n = Math::sqrt(n);

    if (n > 0.000001f) {
      n = 1.0f / n;
      x *= n;
      y *= n;
      z *= n;
    }
  }

  float c = Math::cos(angle);
  float s = Math::sin(angle);

  float t = 1.0f - c;
  float tx = t * x;
  float ty = t * y;
  float tz = t * z;
  float txy = tx * y;
  float txz = tx * z;
  float tyz = ty * z;
  float sx = s * x;
  float sy = s * y;
  float sz = s * z;

  dst[0] = c + tx * x;
  dst[1] = txy + sz;
  dst[2] = txz - sy;
  dst[3] = 0.0f;

  dst[4] = txy - sz;
  dst[5] = c + ty * y;
  dst[6] = tyz + sx;
  dst[7] = 0.0f;

  dst[8] = txz + sy;
  dst[9] = tyz - sx;
  dst[10] = c + tz * z;
  dst[11] = 0.0f;

  dst[12] = 0.0f;
  dst[13] = 0.0f;
  dst[14] = 0.0f;
  dst[15] = 1.0f;
}

void Matrix4::makeEulerRotation(const Vector3& eulerAngles, Matrix4& dst) {
  makeEulerRotation(eulerAngles.x, eulerAngles.y, eulerAngles.z, dst);
}

void Matrix4::makeEulerRotation(float x, float y, float z, Matrix4& dst) {
  Matrix4 my, mz;

  makeRotationAroundX(x, dst);
  makeRotationAroundX(y, my);
  makeRotationAroundX(z, mz);

  multiply(my, dst, dst);
  multiply(mz, dst, dst);
}

void Matrix4::makeRotationAroundX(float angle, Matrix4& dst) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  dst.set(identity());
  dst[5] = cos;
  dst[6] = sin;
  dst[9] = -sin;
  dst[10] = cos;
}

void Matrix4::makeRotationAroundY(float angle, Matrix4& dst) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  dst.set(identity());
  dst[0] = cos;
  dst[2] = -sin;
  dst[8] = sin;
  dst[10] = cos;
}

void Matrix4::makeRotationAroundZ(float angle, Matrix4& dst) {
  float sin = Math::sin(angle);
  float cos = Math::cos(angle);

  dst.set(identity());
  dst[0] = cos;
  dst[1] = sin;
  dst[4] = -sin;
  dst[5] = cos;
}

}
