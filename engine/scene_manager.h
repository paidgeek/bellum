#ifndef __BELLUM_SCENE_MANAGER_H__
#define __BELLUM_SCENE_MANAGER_H__

#include "common.h"

namespace bellum {

class Scene;

class SceneManager {
public:
  DEFINE_EXCEPTION(UnknownSceneNameException, "Unknown scene name");

  static void addScene(const std::string& name, std::unique_ptr<Scene> scene);

  static Scene* currentScene() {
    return current_scene_;
  }

  static void enterScene(const std::string& name);
private:
  SceneManager() {}

  static Scene* current_scene_;
  static std::map<std::string, std::unique_ptr<Scene>> scenes_;
};

}

#endif
