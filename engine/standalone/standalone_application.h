#ifndef BELLUM_DESKTOP_APPLICATION_H
#define BELLUM_DESKTOP_APPLICATION_H

#include "../application.h"

namespace bellum {

class Window;

class StandaloneApplication : public Application {
public:
  StandaloneApplication();
  ~StandaloneApplication();
  DELETE_COPY_AND_ASSIGN(StandaloneApplication);

  void start(int argc, const char* argv[]) override;
  void exit() override;

private:
  std::unique_ptr<Window> window_;
};

}

#endif
