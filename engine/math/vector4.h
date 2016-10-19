#ifndef BELLUM_VECTOR4_H
#define BELLUM_VECTOR4_H

#include "vector3.h"

namespace bellum {

struct Vector4 {
  float x;
  float y;
  float z;
  float w;

  inline Vector4();
  inline Vector4(float x, float y, float z, float w);
  inline Vector4(const float* data);
  inline Vector4(const Vector3& v, float w = 0.0f);
  inline Vector4(const Vector4& from, const Vector4& to);

  inline Vector4(const Vector4& v);
  inline Vector4& operator=(const Vector4& v);

  inline void set(const Vector4& v);
  inline void set(float x, float y, float z, float w);
  inline void set(const float* data);
  inline void setMagnitude(float magnitude);
  inline void setSquaredMagnitude(float sqrMagnitude);

  inline float magnitude() const;
  inline float squaredMagnitude() const;
  inline void normalize(Vector4& dst) const;
  inline Vector4& normalize();
  inline void negate(Vector4& dst) const;
  inline Vector4& negate();

  inline Vector4 operator+(const Vector4& v) const;
  inline Vector4& operator+=(const Vector4& v);
  inline Vector4 operator-(const Vector4& v) const;
  inline Vector4& operator-=(const Vector4& v);
  inline Vector4 operator-() const;
  inline Vector4 operator*(float a) const;
  inline Vector4& operator*=(float a);
  inline Vector4 operator/(float a) const;
  inline Vector4& operator/=(float x);
  inline bool operator==(const Vector4& v) const;
  inline bool operator!=(const Vector4& v) const;

  inline static float dot(const Vector4& a);
  inline static float dot(const Vector4& a, const Vector4& b);
  inline static float angle(const Vector4& from, const Vector4& to);
  inline static void scale(const Vector4& v, float a, Vector4& dst);
  inline static void add(const Vector4& a, const Vector4& b, Vector4& dst);
  inline static void subtract(const Vector4& a, const Vector4& b, Vector4& dst);
  inline static void multiply(const Vector4& a, const Vector4& b, Vector4& dst);
  inline static void divide(const Vector4& a, const Vector4& b, Vector4& dst);

  inline static void clamp(const Vector4& v, const Vector4& min, const Vector4& max, Vector4& dst);
  inline static void clampMagnitude(const Vector4& v, float max, Vector4& dst);
  inline static float distance(const Vector4& a, const Vector4& b);
  inline static float squaredDistance(const Vector4& a, const Vector4& b);
  inline static void lerp(const Vector4& a, const Vector4& b, float t, Vector4& dst);
  inline static Vector4 max(const Vector4& a, const Vector4& b);
  inline static Vector4 min(const Vector4& a, const Vector4& b);
  inline static void project(const Vector4& v, const Vector4& on, Vector4& dst);
  inline static void reflect(const Vector4& in, const Vector4& normal, Vector4& dst);

  inline static const Vector4& zero();
  inline static const Vector4& one();

  inline friend std::ostream& operator<<(std::ostream& os, const Vector4& vector3);
};

// Constructors
inline Vector4::Vector4() {}

inline Vector4::Vector4(float x, float y, float z, float w)
  : x(x), y(y), z(z), w(w) {}

inline Vector4::Vector4(const float* data)
:x(data[0]), y(data[1]), z(data[2]), w(data[3]){}

inline Vector4::Vector4(const Vector3& v, float w)
  : x(v.x), y(v.y), z(v.z), w(w) {}

inline Vector4::Vector4(const Vector4& from, const Vector4& to)
:x(to.x - from.x),y(to.y - from.y),z(to.z - from.z),x(to.w - from.w){}

inline Vector4::Vector4(const Vector4& v)
:x(v.x), y(v.y), z(v.z), w(v.w){}

inline Vector4& Vector4::operator=(const Vector4& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
  return *this;
}

// Setters
inline void Vector4::set(const Vector4& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
}

inline void Vector4::set(float x, float y, float z, float w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

inline void Vector4::set(const float* data) {
  x = data[0];
  y = data[1];
  z = data[2];
  w = data[3];
}

inline void Vector4::setMagnitude(float magnitude) {
  this->setSquaredMagnitude(magnitude * magnitude);
}

inline void Vector4::setSquaredMagnitude(float sqrMagnitude) {
  float sm = this->squaredMagnitude();

  if (sm != 0.0f && sm != sqrMagnitude) {
    float s = Math::sqrt(sqrMagnitude / sm);
    x *= s;
    y *= s;
    z *= s;
    w *= s;
  }
}

// Algebra
inline float Vector4::magnitude() const {
  return Math::sqrt(x * x + y * y + z * z + w * w);
}

inline float Vector4::squaredMagnitude() const {
  return x * x + y * y + z * z + w * w;
}

inline void Vector4::normalize(Vector4& dst) const {
  float m = this->magnitude();

  if (m != 0.0f) {
    dst.x /= m;
    dst.y /= m;
    dst.z /= m;
    dst.w /= m;
  }
}

inline Vector4& Vector4::normalize() {
  float m = this->magnitude();

  if (m != 0.0f) {
    x /= m;
    y /= m;
    z /= m;
    w /= m;
  }

  return *this;
}

inline void Vector4::negate(Vector4& dst) const {
  dst.set(-x, -y, -z, -w);
}

inline Vector4& Vector4::negate() {
  x = -x;
  y = -y;
  z = -z;
  w = -w;
}


// Operators
inline Vector4 Vector4::operator+(const Vector4& v) const {
  return {x + v.x, y + v.y, z + v.z, w + v.w};
}

inline Vector4& Vector4::operator+=(const Vector4& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;
  return *this;
}

inline Vector4 Vector4::operator-(const Vector4& v) const {
  return {x - v.x, y - v.y, z - v.z, w - v.w};
}

inline Vector4& Vector4::operator-=(const Vector4& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;
  return *this;
}

inline Vector4 Vector4::operator-() const {
  return {-x, -y, -z, -w};
}

inline Vector4 Vector4::operator*(float a) const {
  return {x * a, y * a, z * a, w * a};
}

inline Vector4& Vector4::operator*=(float a) {
  x *= a;
  y *= a;
  z *= a;
  w *= a;
  return *this;
}

inline Vector4 Vector4::operator/(const float a) const {
  return {x / a, y / a, z / a, w / a};
}

inline Vector4& Vector4::operator/=(const float a) {
  x /= a;
  y /= a;
  z /= a;
  w /= a;
  return *this;
}

inline bool Vector4::operator==(const Vector4& v) const {
  return x == v.x && y == v.y && z == v.z && w == v.w;
}

inline bool Vector4::operator!=(const Vector4& v) const {
  return x != v.x || y != v.y || z != v.z || w != v.w;
}

inline Vector4 operator*(float a, const Vector4& v) {
  return {
    v.x * a,
    v.x * a,
    v.z * a,
    v.w * a
  };
}

inline float Vector4::dot(const Vector4& a) {
  return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}

inline float Vector4::dot(const Vector4& a, const Vector4& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w + b.w;
}

inline float Vector4::angle(const Vector4& from, const Vector4& to) {
  float dls = dot(from, to) / (from.magnitude() * to.magnitude());

  if (dls < -1.0f) {
    dls = -1.0f;
  } else if (dls > 1.0f) {
    dls = 1.0f;
  }

  return Math::acos(dls);
}

inline void Vector4::scale(const Vector4& v, float a, Vector4& dst) {
  dst.x *= a;
  dst.y *= a;
  dst.z *= a;
  dst.w *= a;
}

inline void Vector4::add(const Vector4& a, const Vector4& b, Vector4& dst) {
  dst.set(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline void Vector4::subtract(const Vector4& a, const Vector4& b, Vector4& dst) {
  dst.set(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

inline void Vector4::multiply(const Vector4& a, const Vector4& b, Vector4& dst) {
  dst.set(a.x * b.x, a.y * b.y, a.z * b.z, a.z * b.z);
}

inline void Vector4::divide(const Vector4& a, const Vector4& b, Vector4& dst) {
  dst.set(a.x / b.x, a.y / b.y, a.z / b.z, a.z / b.z);
}

// Utilities
inline void Vector4::clamp(const Vector4& v, const Vector4& min, const Vector4& max, Vector4& dst) {
  dst.set(
    Math::clamp(v.x, min.x, max.x),
    Math::clamp(v.y, min.y, max.y),
    Math::clamp(v.z, min.z, max.z),
    Math::clamp(v.w, min.w, max.w)
  );
}

inline void Vector4::clampMagnitude(const Vector4& v, float max, Vector4& dst) {
  dst.set(v);

  if (v.magnitude() > max) {
    dst.normalize();
    scale(dst, max, dst);
  }
}

inline float Vector4::distance(const Vector4& a, const Vector4& b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  float dz = b.z - a.z;
  float dw = b.w - a.w;
  return Math::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

inline float Vector4::squaredDistance(const Vector4& a, const Vector4& b) {
  float dx = b.x - a.x;
  float dy = b.y - a.y;
  float dz = b.z - a.z;
  float dw = b.w - a.w;
  return dx * dx + dy * dy + dz * dz + dw * dw;
}

inline void Vector4::lerp(const Vector4& a, const Vector4& b, float t, Vector4& dst) {
  dst.set(
    a.x + (b.x - a.x) * t,
    a.y + (b.y - a.y) * t,
    a.z + (b.z - a.z) * t,
    a.w + (b.w - a.w) * t
  );
}

inline Vector4 Vector4::max(const Vector4& a, const Vector4& b) {
  return {
    Math::max(a.x, b.x),
    Math::max(a.y, b.y),
    Math::max(a.z, b.z),
    Math::max(a.w, b.w)
  };
}

inline Vector4 Vector4::min(const Vector4& a, const Vector4& b) {
  return {
    Math::min(a.x, b.x),
    Math::min(a.y, b.y),
    Math::min(a.z, b.z),
    Math::min(a.w, b.w)
  };
}

inline void Vector4::project(const Vector4& v, const Vector4& on, Vector4& dst) {
  float sm = on.squaredMagnitude();
  dst.set(on * (dot(on, v) / sm));
}

inline void Vector4::reflect(const Vector4& in, const Vector4& normal, Vector4& dst) {
  dst.set(in - 2.0f * dot(in, normal) * normal);
}

// Singletons
const Vector4& Vector4::zero() {
  static Vector4 v{0.0f, 0.0f, 0.0f, 0.0f};
  return v;
}

const Vector4& Vector4::one() {
  static Vector4 v{1.0f, 1.0f, 1.0f, 1.0f};
  return v;
}

inline std::ostream& operator<<(std::ostream& os, const Vector4& v) {
  os << "Vector4(x: " << v.x << ", y: " << v.y << ", z: " << v.z << ", w: " << v.w << ')';
  return os;
}

}

#endif
