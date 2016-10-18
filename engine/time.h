#ifndef __BELLUM_TIME_H__
#define __BELLUM_TIME_H__

#include "common/common.h"

namespace bellum {

class Time {
public:
  static void setTargetUps(double targetUps) {
    target_ups_ = targetUps;
    frame_time_ = 1.0 / targetUps;
  }

  static double getTargetUps() {
    return target_ups_;
  }

  static int32 getFps() {
    return fps_;
  }

  static double getDeltaTime() {
    return dt_;
  }

  static double currentNanoseconds();
  static double currentMicroseconds();
  static double currentMilliseconds();
  static double currentSeconds();

private:
  Time() { }

  static double target_ups_;
  static double frame_time_;
  static int32 fps_;
  static float dt_;

  // timing
  static double current_;
  static double previous_;
  static double elapsed_;
  static double lag_;
  static double last_fps_update_;
  static int32 frames_processed_;
};

}

#endif
