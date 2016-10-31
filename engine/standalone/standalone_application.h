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

  void start(std::vector<std::string> args) override;
  void exit() override;

private:
  using super = Application;

  std::unique_ptr<Window> window_;
};

}

#endif
