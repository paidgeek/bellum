#ifndef __BELLUM_SCENE_MANAGER_H__
#define __BELLUM_SCENE_MANAGER_H__

#include "common/common.h"
#include "scene.h"

namespace bellum {

class SceneManager {
public:
  DEFINE_EXCEPTION(UnknownSceneNameException, "Unknown scene name");

  template<typename T>
  void addScene(const std::string& name) {
    scenes_.insert(std::make_pair(name, std::make_unique<T>()));

    if (scenes_.size() == 1) {
      current_scene_ = scenes_.begin()->second.get();
    }
  }

  Scene* currentScene() {
    return current_scene_;
  }

  void update() {
  }

  void enterScene(const std::string& name);
private:
  Scene* current_scene_;
  std::map<std::string, std::unique_ptr<Scene>> scenes_;
};

}

#endif
