#ifndef __BELLUM_SCENE_MANAGER_H__
#define __BELLUM_SCENE_MANAGER_H__

#include "common.h"

namespace bellum {

class Scene;

class SceneManager {
public:
  DEFINE_EXCEPTION(UnknownSceneNameException, "Unknown scene name");

  SceneManager() {}

  void addScene(const std::string& name, std::unique_ptr<Scene> scene);

  Scene* currentScene() {
    return current_scene_;
  }

  void enterScene(const std::string& name);
private:
  Scene* current_scene_;
  std::map<std::string, std::unique_ptr<Scene>> scenes_;
};

}

#endif
