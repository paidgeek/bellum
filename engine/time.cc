#include "time.h"
#include <GLFW/glfw3.h>

namespace bellum {

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
