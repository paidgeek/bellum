#ifndef __BELLUM_CAMERA_H__
#define __BELLUM_CAMERA_H__

#include "../common.h"
#include "../component.h"
#include "../math/matrix4.h"
#include "../color.h"

namespace bellum {

class Camera : public Component {
public:
  enum class ClearFlags {
    SOLID_COLOR, DEPTH, NOTHING
  };

  const Matrix4& projection() const {
    return projection_;
  }

  void setProjection(const Matrix4& projection) {
    projection_ = projection;
  }

  ClearFlags clearFlags() const {
    return clear_flags_;
  }

  void setClearFlags(ClearFlags clearFlags) {
    clear_flags_ = clearFlags;
  }

  Color clearColor() const {
    return clear_color_;
  }

  void setClearColor(const Color& color) {
    clear_color_ = color;
  }

  Matrix4 viewProjection() const;
  Matrix4 view() const;
  Vector3 worldToViewportPoint(const Vector3& worldPoint) const;

  static Camera* mainCamera() {
    return mainCamera_;
  }

  static void setMainCamera(Camera* camera) {
    mainCamera_ = camera;
  }

private:
  Matrix4 projection_;
  ClearFlags clear_flags_;
  Color clear_color_;

  static Camera* mainCamera_;
};

}

#endif
