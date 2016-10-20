#ifndef BELLUM_APPLICATION_H
#define BELLUM_APPLICATION_H

#include "common/common.h"
#include "scene_manager.h"

namespace bellum {

class Application {
public:
  virtual void start(int argc, const char* argv[]) = 0;
  virtual void exit() = 0;

  template<typename T>
  void addScene(const std::string& name) {
    scene_manager_.addScene<T>(name);
  }

  Logger* getLogger() {
    return logger_.get();
  }

  static Application* getInstance();
protected:
  Application();

  std::unique_ptr<Logger> logger_;
  SceneManager scene_manager_;
  bool running_;
};

}

#endif
