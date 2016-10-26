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
  Transform() {}

  void translate(const Vector3& translation, Space space = Space::SELF) {
    translate(translation.x, translation.y, translation.z, space);
  }

  void translate(float x, float y, float z, Space space = Space::SELF) {
    if (space == Space::WORLD) {
      position_ += Vector3{x, y, z};
    } else {
      position_ += rotation_ * Vector3{x, y, z};
    }
  }

  void rotate(float x, float y, float z, Space space = Space::WORLD) {
    rotate(Vector3{x, y, z}, space);
  }

  void rotate(const Vector3& euler, Space space = Space::WORLD) {
    rotate(Quaternion::makeEuler(euler), space);
  }

  void rotate(float angle, const Vector3& axis, Space space = Space::WORLD) {
    rotate(Quaternion::makeAngleAxis(angle, axis), space);
  }

  void rotate(const Quaternion& rotation, Space space = Space::WORLD) {
    if (space == Space::WORLD) {
      rotation_ = rotation * rotation_;
    } else {
      rotation_ = rotation_ * rotation;
    }

    rotation_.normalize();
  }

  inline Vector3 position() {
    return parentMatrix() * position_;
  }

  inline void setPosition(const Vector3& position) {
    position_ = parentMatrix().inverse() * position;
  }

  inline const Vector3& localPosition() {
    return position_;
  }

  inline void setLocalPosition(const Vector3& position) {
    position_ = position;
  }

  inline Quaternion rotation() {
    if (parent_ != nullptr) {
      return parent_->rotation() * rotation_;
    }

    return rotation_;
  }

  inline void setRotation(const Quaternion& rotation) {
    rotation_ = parent_->rotation().inverse() * rotation;
  }

  inline const Quaternion& localRotation() const {
    return rotation_;
  }

  inline void setLocalRotation(const Quaternion& rotation) {
    rotation_ = rotation;
  }

  inline Vector3 scale() {
    if (parent_ != nullptr) {
      return Vector3::scale(parent_->scale(), scale_);
    }

    return scale_;
  }

  inline void setScale(const Vector3& scale) {
    Vector3 ps = parent_->scale();
    scale_.set(1.0f / ps.x, 1.0f / ps.y, 1.0f / ps.z);
  }

  inline const Vector3& localScale() const {
    return scale_;
  }

  inline void setLocalScale(const Vector3& scale) {
    scale_ = scale;
  }

  inline Transform* parent() {
    return parent_;
  }

  inline void setParent(Transform* parent, bool worldPositionStays = false) {
    if (worldPositionStays) {
      position_ = parent->localToWorld().inverse() * position_;
      rotation_ = parent_->rotation().inverse() * rotation_;
      Vector3 ps = parent->scale();
      scale_.set(scale_.x / ps.x, scale_.y / ps.y, scale_.z / ps.z);
    }

    parent_ = parent;
  }

  inline Matrix4 localToWorld() {
    return parentMatrix() * Matrix4::makeTransformation(position_, rotation_, scale_);
  }

  inline Vector3 forward() {
    return rotation() * Vector3::forward();
  }

  inline Vector3 back() {
    return rotation() * Vector3::back();
  }

  inline Vector3 right() {
    return rotation() * Vector3::right();
  }

  inline Vector3 left() {
    return rotation() * Vector3::left();
  }

  inline Vector3 up() {
    return rotation() * Vector3::up();
  }

  inline Vector3 down() {
    return rotation() * Vector3::down();
  }

private:
  Vector3 position_{};
  Quaternion rotation_{};
  Vector3 scale_{1.0f, 1.0f, 1.0f};

  Transform* parent_ = nullptr;
  Matrix4 parent_matrix_{};

  inline Matrix4& parentMatrix() {
    if (parent_ != nullptr) {
      parent_matrix_ = parent_->localToWorld();
    }

    return parent_matrix_;
  }
};

}

#endif
