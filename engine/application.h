#ifndef BELLUM_APPLICATION_H
#define BELLUM_APPLICATION_H

#include "common/common.h"

namespace bellum {

class Application {
public:
  virtual void start(int argc, char* argv[]) = 0;
  virtual void exit() = 0;

  static Application* getPlatformApplication();
};

}

#endif
