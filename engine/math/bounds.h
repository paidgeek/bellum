#ifndef __BELLUM_BOUNDS_H__
#define __BELLUM_BOUNDS_H__

#include "../common.h"
#include "vector3.h"

namespace bellum {

struct Bounds {
  Vector3 center;
  Vector3 size;

  inline Bounds(const Vector3& center, const Vector3& size);
  inline Bounds(const Bounds& other);
  inline Bounds& operator=(const Bounds& other);

  inline void setMinMax(const Vector3& min, const Vector3& max);
  inline Vector3 min() const;
  inline Vector3 max() const;
  inline Vector3 extents() const;

  inline Vector3 closestPoint(const Vector3& point) const;
  inline bool contains(const Vector3& point) const;
  inline bool contains(const Bounds& bounds) const;
  inline bool overlaps(const Bounds& bounds) const;
  inline void encapsulate(const Vector3& point);
  inline void expand(float amount);
  inline float squaredDistance(const Vector3& point) const;
};

Bounds::Bounds(const Vector3& center, const Vector3& size)
  : center(center), size(size) {}

Bounds::Bounds(const Bounds& other)
  : center(other.center), size(other.size) {}

Bounds& Bounds::operator=(const Bounds& other) {
  center = other.center;
  size = other.size;
}

inline void Bounds::setMinMax(const Vector3& min, const Vector3& max) {
  size = max - min;
  center = min + size / 2.0f;
}

inline Vector3 Bounds::min() const {
  return center - size / 2.0f;
}

inline Vector3 Bounds::max() const {
  return center + size / 2.0f;
}

inline Vector3 Bounds::extents() const {
  return size / 2.0f;
}

inline Vector3 Bounds::closestPoint(const Vector3& point) const {
  Vector3 hs = size / 2.0f;
  Vector3 min = center - hs;
  Vector3 max = center + hs;
  return {
    Math::clamp(point.x, min.x, max.x),
    Math::clamp(point.y, min.y, max.y),
    Math::clamp(point.z, min.z, max.z)
  };
}

inline bool Bounds::contains(const Vector3& point) const {
  if (point.x < center.x) return false;
  if (point.y < center.y) return false;
  if (point.z < center.z) return false;
  if (point.x > center.x + size.x) return false;
  if (point.y > center.y + size.y) return false;
  if (point.z > center.z + size.z) return false;

  return true;
}

inline bool Bounds::contains(const Bounds& bounds) const {
  Vector3 a = center;
  Vector3 a2 = center + size;
  Vector3 b = bounds.center;
  Vector3 b2 = bounds.center + bounds.size;

  return a.x <= b.x &&
         a2.x > b2.x &&
         a.y <= b.y &&
         a2.y > b2.y &&
         a.z <= b.z &&
         a2.z > b2.z;
}

inline bool Bounds::overlaps(const Bounds& bounds) const {
  if (center.x >= bounds.center.x + bounds.size.x) return false;
  if (center.x + size.x <= bounds.center.x) return false;
  if (center.y >= bounds.center.y + bounds.size.y) return false;
  if (center.y + size.y <= bounds.center.y) return false;
  if (center.z >= bounds.center.z + bounds.size.z) return false;
  if (center.z + size.z <= bounds.center.z) return false;

  return true;
}

inline void Bounds::encapsulate(const Vector3& point) {
  Vector3 a = center;
  Vector3 b = center + size;

  if (point.x < a.x)
    a.x = point.x;
  if (point.y < a.y)
    a.y = point.y;
  if (point.z < a.z)
    a.z = point.z;
  if (point.x > b.x)
    b.x = point.x;
  if (point.y > b.y)
    b.y = point.y;
  if (point.z > b.z)
    b.z = point.z;

  center = a;
  size = b - a;
}

inline void Bounds::expand(float amount) {
  center.x -= amount;
  center.y -= amount;
  center.z -= amount;
  size.x += 2.0f * amount;
  size.y += 2.0f * amount;
  size.z += 2.0f * amount;
}

inline float Bounds::squaredDistance(const Vector3& point) const {
  return Vector3::squaredDistance(point, closestPoint(point));
}

}

#endif
