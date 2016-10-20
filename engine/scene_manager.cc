#include "scene_manager.h"
#include "scene.h"

namespace bellum {

void SceneManager::addScene(const std::string& name, std::unique_ptr<Scene> scene) {
  scenes_.insert(std::make_pair(name, std::move(scene)));
  if (scenes_.size() == 1) {
    current_scene_ = scenes_.begin()->second.get();
  }
}

void SceneManager::enterScene(const std::string& name) {
  auto e = scenes_.find(name);
  if (e != scenes_.end()) {
    current_scene_ = e->second.get();
  } else {
    throw UnknownSceneNameException{};
  }
}

}
