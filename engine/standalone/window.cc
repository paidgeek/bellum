#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "input.h"

namespace bellum {

Window::Window(int32 width, int32 height)
  : width_(width), height_(height) {}

void Window::show() {
  if(!glfwInit()) {
    throw ShowException{};
  }

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  glfw_window_ = glfwCreateWindow(width_, height_, "Bellum", NULL, NULL);
  if (!glfw_window_) {
    glfwTerminate();
    throw ShowException{};
  }

  // setup input
  Input::setWindow(glfw_window_);
  Input::setupCallbacks();

  glfwMakeContextCurrent(glfw_window_);
  glfwSetErrorCallback([](int32 error, const char* description) {
    std::cerr << description << std::endl;
  });
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glewExperimental = GL_TRUE;
  glewInit();
}

void Window::update() {
  Input::update();
}

void Window::render() {
  glfwSwapBuffers(glfw_window_);
  glfwPollEvents();
}

bool Window::shouldClose() {
  return glfwWindowShouldClose(glfw_window_) != GL_FALSE;
}

void Window::close() {
  glfwTerminate();
}

}
