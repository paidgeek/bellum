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
      if(Input::mousePressed(Input::MOUSE_BUTTON_1)) {
        Input::setMouseLocked(true);
      }

      return;
    }

    Vector2 mouseDelta = Input::mouseDelta();
    Transform* t = &node_->transform();
    float dt = Time::deltaTime();

    if (mouseDelta.x != 0.0f) {
      t->rotate(0.0f, mouseDelta.x * kMouseSensitivity * dt, 0.0f);
    }

    if (mouseDelta.y != 0.0f) {
      t->rotate(mouseDelta.y * kMouseSensitivity * dt, t->right());
    }

    if (Input::keyPressed(Input::KEY_W)) {
      t->translate(t->forward() * kSpeed * dt, Space::WORLD);
    }

    if (Input::keyPressed(Input::KEY_S)) {
      t->translate(t->back() * kSpeed * dt, Space::WORLD);
    }

    if (Input::keyPressed(Input::KEY_A)) {
      t->translate(t->left() * kSpeed * dt, Space::WORLD);
    }

    if (Input::keyPressed(Input::KEY_D)) {
      t->translate(t->right() * kSpeed * dt, Space::WORLD);
    }

    if(Input::keyPressed(Input::KEY_E)){
      t->translate(Vector3::up() * kSpeed * dt, Space::WORLD);
    }

    if(Input::keyPressed(Input::KEY_Q)){
      t->translate(Vector3::down() * kSpeed * dt, Space::WORLD);
    }

    if (Input::keyPressed(Input::KEY_ESCAPE)) {
      Input::setMouseLocked(false);
    }
  }
};

#endif
