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

  static double deltaTime() {
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

class FixedTimeStepTimer {
public:
  FixedTimeStepTimer(double targetUps);

  void start();
  void update();
  bool doUpdate();
  void doRender();

private:
  double target_ups_;
  double frame_time_;
  int32 fps_;
  float dt_;

  double current_;
  double previous_;
  double elapsed_;
  double lag_;
  float lag_offset_;
  double last_fps_update_;
  int32 frames_processed_;
};

}

#endif
