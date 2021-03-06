#ifndef BELLUM_WINDOW_H
#define BELLUM_WINDOW_H

#include "../common.h"

struct GLFWwindow;

namespace bellum {

class Window {
public:
  DEFINE_EXCEPTION(ShowException, "Cannot show window");

  Window(int32 width, int32 height);

  void show();
  bool shouldClose();
  void update();
  void render();
  void close();

private:
  int32 width_;
  int32 height_;
  GLFWwindow* glfw_window_;
};

}

#endif
