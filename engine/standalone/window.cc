#include "window.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace bellum {

void Window::show() {
  if (!glfwInit()) {
    throw ShowException{};
  }

  glfw_window_ = glfwCreateWindow(width_, height_, "Bellum", NULL, NULL);
  if(!glfw_window_) {
    glfwTerminate();
    throw ShowException{};
  }

  glfwMakeContextCurrent(glfw_window_);

  while (!glfwWindowShouldClose(glfw_window_)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(glfw_window_);

    glfwPollEvents();
  }
}

void Window::close() {
  glfwTerminate();
}

}
