#ifndef __BELLUM_APPLICATION_H__
#define __BELLUM_APPLICATION_H__

#include "common.h"
#include "render/render_module.h"
#include "update/update_module.h"

namespace bellum {

class Scene;

class Application {
  friend class Renderer;
  friend class Scene;
  friend class Node;

public:
  Application();

  virtual void start(int argc, const char* argv[]) = 0;
  virtual void exit() = 0;

  Logger* logger() {
    return logger_.get();
  }

  void addScene(const std::string& name, std::unique_ptr<Scene> scene);

  static Application* instance();
protected:
  void onStart();
  void update();
  void render();

  std::unique_ptr<Logger> logger_;
  bool running_;

private:
  std::unique_ptr<UpdateModule> update_module_;
  std::unique_ptr<RenderModule> render_module_;
};

}

#endif
