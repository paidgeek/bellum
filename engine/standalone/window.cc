#include "window.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace bellum {

Window::Window(int32 width, int32 height)
  : width_(width), height_(height) {}

void Window::show() {
  if (!glfwInit()) {
    throw ShowException{};
  }

  glfw_window_ = glfwCreateWindow(width_, height_, "Bellum", NULL, NULL);
  if (!glfw_window_) {
    glfwTerminate();
    throw ShowException{};
  }

  glfwMakeContextCurrent(glfw_window_);
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
