#include "vector3.h"

namespace bellum {

// Utilities
Vector3& Vector3::clamp(const Vector3& min, const Vector3& max) {
  x = Math::clamp(x, min.x, max.x);
  y = Math::clamp(y, min.y, max.y);
  z = Math::clamp(z, min.z, max.z);
}

void Vector3::clamp(const Vector3& v, const Vector3& min, const Vector3& max, Vector3* dst) {
  dst->set(v);
  dst->clamp(min, max);
}

Vector3& Vector3::clampMagnitude(float max) {
  float m = this->magnitude();

  if(m > max){
    this->normalize();
    this->scale(max);
  }

  return *this;
}

void Vector3::clampMagnitude(const Vector3& v, float max, Vector3* dst) {
  dst->set(v);
  dst->clampMagnitude(max);
}

float Vector3::distance(const Vector3& a, const Vector3& b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  float dz = b.z - a.z;
  return Math::sqrt(dx * dx + dy * dy + dz * dz);
}

float Vector3::squaredDistance(const Vector3& a, const Vector3& b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  float dz = b.z - a.z;
  return dx * dx + dy * dy + dz * dz;
}

Vector3& Vector3::lerp(const Vector3& b, float t) {
  x += (b.x - x) * t;
  y += (b.y - y) * t;
  z += (b.z - z) * t;
  return *this;
}

void Vector3::lerp(const Vector3& a, const Vector3& b, float t, Vector3* dst) {
  dst->set(a);
  dst->lerp(b, t);
}

Vector3 Vector3::max(const Vector3& a, const Vector3& b) {
  return {
    Math::max(a.x, b.x),
    Math::max(a.y, b.y),
    Math::max(a.z, b.z)
  };
}

Vector3 Vector3::min(const Vector3& a, const Vector3& b) {
  return {
    Math::min(a.x, b.x),
    Math::min(a.y, b.y),
    Math::min(a.z, b.z)
  };
}

Vector3& Vector3::project(const Vector3& on) {
  project(*this, on, this);
  return *this;
}

void Vector3::project(const Vector3& v, const Vector3& on, Vector3* dst) {
  float sm = on.squaredMagnitude();
  dst->set(on * (dot(on, v) / sm));
}

Vector3& Vector3::reflect(const Vector3& normal) {
  reflect(*this, normal, this);
  return *this;
}

void Vector3::reflect(const Vector3& in, const Vector3& normal, Vector3* dst) {
  dst->set(in - 2.0f * dot(in, normal) * normal);
}

Vector3& Vector3::slerp(const Vector3& b, float t) {
  float d = dot(b);

  if (d > 0.9995f || d < -0.9995f) {
    this->lerp(b, t);
    return *this;
  }

  float theta0 = Math::acos(d);
  float theta = theta0 * t;

  float st = Math::sin(theta);
  float tx = b.x - x * d;
  float ty = b.y - y * d;
  float tz = b.z - z * d;
  float l2 = tx * tx + ty * ty + tz * tz;
  float dl = st * ((l2 < 0.0001f) ? 1.0f : 1.0f / Math::sqrt(l2));

  this->scale(Math::cos(theta));
  this->add(tx * dl, ty * dl, tz * dl);
  this->normalize();

  return *this;
}

void Vector3::slerp(const Vector3& a, const Vector3& b, float t, Vector3* dst) {
  dst->set(a);
  dst->slerp(b, t);
}

Vector3& Vector3::rotate(const Vector3& axis, float angle) {
  float sin = Math::sin(-angle);
  float cos = Math::cos(-angle);

  this->cross(axis * sin);
  this->add(x * cos, y * cos, z * cos);
  this->add(axis * dot(*this, axis * (1.0f - cos)));

  return *this;
}

void Vector3::rotate(const Vector3& v, const Vector3& axis, float angle, Vector3* dst) {
  dst->set(v);
  dst->rotate(axis, angle);
}

}
