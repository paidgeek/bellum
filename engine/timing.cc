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

FixedTimeStepTimer::FixedTimeStepTimer(double targetUps)
  : target_ups_(targetUps), frame_time_(1.0 / targetUps) {}

void FixedTimeStepTimer::start() {
  dt_ = static_cast<float >(frame_time_);
  Time::setDeltaTime(dt_);

  lag_ = 0.0;
  last_fps_update_ = 0.0;
  frames_processed_ = 0;

  previous_ = Time::currentSeconds();
}

void FixedTimeStepTimer::update() {
  current_ = Time::currentSeconds();
  elapsed_ = current_ - previous_;
  lag_ += elapsed_;
}

bool FixedTimeStepTimer::doUpdate() {
  bool b = lag_ > frame_time_;
  lag_ -= frame_time_;
  return b;
}

void FixedTimeStepTimer::doRender() {
  lag_offset_ = static_cast<float>(lag_ / frame_time_);
  frames_processed_++;

  if (current_ - last_fps_update_ >= 1.0) {
    Time::setFps(frames_processed_);
    frames_processed_ = 0;
  }

  previous_ = current_;
}

}
