#include "input.h"
#include <GLFW/glfw3.h>

namespace bellum {

GLFWwindow* Input::glfw_window_;
bool Input::mouse_locked_;
Vector2 Input::mouse_position_;
Vector2 Input::mouse_delta_;
float Input::scroll_x_;
float Input::scroll_y_;

void Input::setupCallbacks() {
  glfwSetScrollCallback(glfw_window_, [](GLFWwindow* window, double xoffset, double yoffset) {
    scroll_x_ = static_cast<float>(xoffset);
    scroll_y_ = static_cast<float>(yoffset);
  });
}

bool Input::keyPressed(uint16 keyCode) {
  return glfwGetKey(glfw_window_, keyCode) == GLFW_PRESS;
}

bool Input::keyReleased(uint16 keyCode) {
  return glfwGetKey(glfw_window_, keyCode) == GLFW_RELEASE;
}

bool Input::keyRepeated(uint16 keyCode) {
  return glfwGetKey(glfw_window_, keyCode) == GLFW_REPEAT;
}

bool Input::mousePressed(uint16 button) {
  return glfwGetMouseButton(glfw_window_, button) == GLFW_PRESS;
}

bool Input::mouseReleased(uint16 button) {
  return glfwGetMouseButton(glfw_window_, button) == GLFW_RELEASE;
}

bool Input::mouseRepeated(uint16 button) {
  return glfwGetMouseButton(glfw_window_, button) == GLFW_REPEAT;
}

void Input::setMouseLocked(bool locked) {
  mouse_locked_ = locked;
  glfwSetInputMode(glfw_window_, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Input::update() {
  double x, y;
  glfwGetCursorPos(glfw_window_, &x, &y);
  Vector2 mp{static_cast<float>(x), static_cast<float>(y)};

  mouse_delta_ = mp - mouse_position_;
  mouse_position_ = mp;

  scroll_x_ = 0.0f;
  scroll_y_ = 0.0f;
}

}
