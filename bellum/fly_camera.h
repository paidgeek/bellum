#ifndef __BELLUM_FLY_CAMERA_H__
#define __BELLUM_FLY_CAMERA_H__

#include <bellum.h>

using namespace bellum;

class FlyCamera : public Component {
public:
  static constexpr float kSpeed = 10.0f;
  static constexpr float kMouseSensitivity = 0.25f;

  void update() override {
    if(!Input::mouseLocked()) {
      if(Input::mouseButtonDown(Input::MOUSE_BUTTON_1)) {
        Input::setMouseLocked(true);
      }

      return;
    }

    Vector2 mouseDelta = Input::mouseDelta();
    Transform* t = &node_->transform();
    float dt = kSpeed * Time::deltaTime();

    if (mouseDelta.x != 0.0f) {
      t->rotate(0.0f, mouseDelta.x * kMouseSensitivity * dt, 0.0f);
    }

    if (mouseDelta.y != 0.0f) {
      t->rotate(mouseDelta.y * kMouseSensitivity * dt, t->right());
    }

    if (Input::keyDown(Input::KEY_W)) {
      t->translate(t->forward() * dt);
    }

    if (Input::keyDown(Input::KEY_S)) {
      t->translate(t->back() * dt);
    }

    if (Input::keyDown(Input::KEY_A)) {
      t->translate(t->left() * dt);
    }

    if (Input::keyDown(Input::KEY_D)) {
      t->translate(t->right() * dt);
    }

    if (Input::keyDown(Input::KEY_ESCAPE)) {
      Input::setMouseLocked(false);
    }
  }
};

#endif
