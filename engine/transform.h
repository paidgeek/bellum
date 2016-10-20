#ifndef __BELLUM_TRANSFORM_H__
#define __BELLUM_TRANSFORM_H__

#include "common.h"
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

  void translate(const Vector3& translation, Space space = Space::SELF) {
    translate(translation.x, translation.y, translation.z, space);
  }

  void translate(float x, float y, float z, Space space = Space::SELF) {
    if (space == Space::WORLD) {
      position_ += {x, y, z};
    } else {
      position_ += rotation_ * Vector3{x, y, z};
    }
  }

  void rotate(float x, float y, float z, Space space = Space::WORLD) {
    rotate(Vector3{x, y, z}, space);
  }

  void rotate(const Vector3& eulerAngles, Space space = Space::WORLD) {
    Quaternion rotation;
    Quaternion::makeEuler(eulerAngles, rotation);
    this->rotate(rotation, space);
  }

  void rotate(const Vector3& axis, float angle, Space space = Space::WORLD) {
    Quaternion rotation;
    Quaternion::makeAxisAngle(axis, angle, rotation);
    this->rotate(rotation, space);
  }

  void rotate(const Quaternion& rotation, Space space = Space::WORLD) {
    if(space == Space::WORLD) {
      rotation_.set(rotation * rotation_);
    } else {
      rotation_.set(rotation_ * rotation);
    }

    rotation_.normalize();
  }

  inline Vector3 position() {
    return parentMatrix() * position_;
  }

  inline void setPosition(const Vector3& position) {
    position_.set(parentMatrix().inverse() * position);
  }

  inline const Vector3& localPosition() {
    return position_;
  }

  inline void setLocalPosition(const Vector3& position) {
    position_.set(position);
  }

  inline Quaternion rotation() {
    if (parent_ != nullptr) {
      return parent_->rotation() * rotation_;
    }

    return rotation_;
  }

  inline void setRotation(const Quaternion& rotation) {
    rotation_.set(parent_->rotation().inverse() * rotation);
  }

  inline const Quaternion& localRotation() const {
    return rotation_;
  }

  inline void setLocalRotation(const Quaternion& rotation) {
    rotation_.set(rotation);
  }

  inline Vector3 scale() {
    if (parent_ != nullptr) {
      return parent_->scale() * scale_;
    }

    return scale_;
  }

  inline void setScale(const Vector3& scale) {
    scale_.set(scale / parent_->scale());
  }

  inline const Vector3& localScale() const {
    return scale_;
  }

  inline void setLocalScale(const Vector3& scale) {
    scale_.set(scale);
  }

  inline Transform* parent() {
    return parent_;
  }

  inline void setParent(Transform* parent, bool worldPositionStays = false) {
    if (worldPositionStays) {
      position_ = parent->localToWorld().inverse() * position_;
      rotation_ = parent_->rotation().inverse() * rotation_;
      scale_ = scale_ / parent->scale();
    }

    parent_ = parent;
  }

  inline Matrix4 localToWorld() {
    Matrix4 t, r, s;
    Matrix4::makeTranslation(position_, t);

    return parent_matrix_ * t * r * s;
  }

  inline Vector3 forward() {
    Vector3 result;
    Quaternion::rotatePoint(rotation(), Vector3::forward(), result);
    return result;
  }

  inline Vector3 back() {
    Vector3 result;
    Quaternion::rotatePoint(rotation(), Vector3::back(), result);
    return result;
  }

  inline Vector3 right() {
    Vector3 result;
    Quaternion::rotatePoint(rotation(), Vector3::right(), result);
    return result;
  }

  inline Vector3 left() {
    Vector3 result;
    Quaternion::rotatePoint(rotation(), Vector3::left(), result);
    return result;
  }

  inline Vector3 up() {
    Vector3 result;
    Quaternion::rotatePoint(rotation(), Vector3::up(), result);
    return result;
  }

  inline Vector3 down() {
    Vector3 result;
    Quaternion::rotatePoint(rotation(), Vector3::down(), result);
    return result;
  }
private:
  Vector3 position_;
  Quaternion rotation_;
  Vector3 scale_;

  Transform* parent_;
  Matrix4 parent_matrix_;

  inline Matrix4& parentMatrix() {
    if (parent_ != nullptr) {
      parent_matrix_ = parent_->localToWorld();
    }

    return parent_matrix_;
  }
};

}

#endif
