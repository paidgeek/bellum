#ifndef __BELLUM_TIME_H__
#define __BELLUM_TIME_H__

#include "common.h"

namespace bellum {

class Time {
public:
  static int32 fps() {
    return fps_;
  }

  static void setFps(int32 fps) {
    fps_ = fps;
  }

  static float deltaTime() {
    return dt_;
  }

  static void setDeltaTime(float dt) {
    dt_ = dt;
  }

  static double currentNanoseconds();
  static double currentMicroseconds();
  static double currentMilliseconds();
  static double currentSeconds();

private:
  static int32 fps_;
  static float dt_;

  Time() {}
};

}

#endif
