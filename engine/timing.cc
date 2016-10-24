#include "timing.h"
#include <GLFW/glfw3.h>

namespace bellum {

int32 Time::fps_ = 0;
float Time::dt_ = 0.0f;

double Time::currentNanoseconds() {
  return glfwGetTime() * 1000000000.0;
}

double Time::currentMicroseconds() {
  return glfwGetTime() * 1000000.0;
}

double Time::currentMilliseconds() {
  return glfwGetTime() * 1000.0;
}

double Time::currentSeconds() {
  return glfwGetTime();
}

}
