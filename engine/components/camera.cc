#include "camera.h"
#include "../node.h"

namespace bellum {

Matrix4 Camera::viewProjection() const {
  return projection_ * view();
}

Matrix4 Camera::view() const {
  Transform* t = &node_->transform();

  return Matrix4::makeRotation(t->rotation().conjugated()) *
         Matrix4::makeTranslation(-t->position());
}

Vector3 Camera::worldToViewportPoint(const Vector3& worldPoint) const {
  Vector3 viewport = viewProjection() * worldPoint;

  viewport.x /= viewport.z;
  viewport.y /= viewport.z;
  viewport.x = (viewport.x + 1.0f) / 2.0f;
  viewport.y = (viewport.y + 1.0f) / 2.0f;

  return viewport;
}

}
