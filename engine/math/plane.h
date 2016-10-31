#ifndef BELLUM_PLANE_H
#define BELLUM_PLANE_H

#include "vector3.h"

namespace bellum {

struct Plane {
  enum class Intersection : uint8 {
    INTERSECTS,
    FRONT,
    BACK
  };

  Vector3 normal;
  float distance;

  Plane();
  Plane(const Vector3& normal, float distance);
  Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3);

  Plane& normalize();
  void normalize(Plane* dst) const;

  float pointDistance(const Vector3& point) const;
  static float pointDistance(const Plane& p, const Vector3& point);

};

}

#endif
