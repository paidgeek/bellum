#ifndef __BELLUM_TRANSFORM_H__
#define __BELLUM_TRANSFORM_H__

#include "common/common.h"
#include "math/vector3.h"
#include "math/quaternion.h"
#include "math/matrix4.h"

namespace bellum {

enum class Space {
  SELF,
  WORLD
};

class Transform {
public:
  Transform()
    : scale_({1.0f, 1.0f, 1.0f}) {}

  inline Vector3& position() {
    return position_;
  }

  inline const Quaternion& rotation() {
    return rotation_;
  }

  inline Vector3& scale() {
    return scale_;
  }

  Transform* parent() {
    return parent_;
  }

  void setParent(Transform* parent, bool worldPositionStays = false) {
    if(worldPositionStays) {

    }

    parent_ = parent;
  }

  Matrix4 localToWorld() {
    Matrix4 t, r, s;
    Matrix4::makeTranslation(position_, &t);

    return parent_matrix_ * t * r * s;
  }
private:
  Vector3 position_;
  Quaternion rotation_;
  Vector3 scale_;

  Transform* parent_;
  Matrix4 parent_matrix_;
};

}

#endif
