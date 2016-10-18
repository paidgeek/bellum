#ifndef BELLUM_DESKTOP_APPLICATION_H
#define BELLUM_DESKTOP_APPLICATION_H

#include "../application.h"
#include "window.h"

namespace bellum {

class StandaloneApplication : public Application {
public:
  StandaloneApplication() {}

  void start(int argc, const char* argv[]) override;
  void exit() override;

private:
  bool is_running_;
  std::unique_ptr<Window> window_;
};

}

#endif
