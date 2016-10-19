#include "scene_manager.h"

namespace bellum {

void SceneManager::enterScene(const std::string& name) {
  auto e = scenes_.find(name);
  if (e != scenes_.end()) {
    current_scene_ = e->second.get();
  } else {
    throw UnknownSceneNameException{};
  }
}

}
