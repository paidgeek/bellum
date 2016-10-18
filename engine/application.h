#ifndef BELLUM_APPLICATION_H
#define BELLUM_APPLICATION_H

#include "common/common.h"
#include "scene.h"

namespace bellum {

class RenderModule;

class Application {
public:
  Application() {}
  DELETE_COPY_AND_ASSIGN(Application);

  virtual void start(int argc, const char* argv[]) = 0;
  virtual void exit() = 0;

  template<typename T>
  void addScene() {
    scenes_.emplace_back(new T{});
  }

  Logger* getLogger() {
    return logger_.get();
  }

  static Application* getInstance();
protected:
  std::unique_ptr<Logger> logger_;
private:
  std::vector<std::unique_ptr<Scene>> scenes_;
  RenderModule* render_module_;
};

}

#endif
