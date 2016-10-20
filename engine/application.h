#ifndef __BELLUM_APPLICATION_H__
#define __BELLUM_APPLICATION_H__

#include "common.h"

namespace bellum {

class SceneManager;
class UpdateModule;
class RenderModule;
class Scene;

class Application {
public:
  Application();

  virtual void start(int argc, const char* argv[]) = 0;
  virtual void exit() = 0;

  Logger* logger() {
    return logger_.get();
  }

  void addScene(const std::string& name, std::unique_ptr<Scene> scene);

  static Application* getInstance();
protected:
  void onStart();
  void update();
  void render();

  std::unique_ptr<Logger> logger_;
  bool running_;

private:
  std::shared_ptr<SceneManager> scene_manager_;
  std::shared_ptr<UpdateModule> update_module_;
  std::shared_ptr<RenderModule> render_module_;
};

}

#endif
