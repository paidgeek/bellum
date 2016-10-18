#ifndef BELLUM_DESKTOP_APPLICATION_H
#define BELLUM_DESKTOP_APPLICATION_H

#include "../application.h"
#include "window.h"

namespace bellum {

class StandaloneApplication : public Application {
public:
  StandaloneApplication();

  DELETE_COPY_AND_ASSIGN(StandaloneApplication);

  void start(int argc, char* argv[]) override;
  void exit() override;

private:
  Logger logger_;
  std::shared_ptr<Window> window_;
};

}

#endif
