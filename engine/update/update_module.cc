#include "../scene.h"
#include "update_module.h"
#include "../component.h"

namespace bellum {

void UpdateModule::onStart(Scene* scene) {
  scene_ = scene;
}

void UpdateModule::update() {
  for (auto& node : scene_->nodes()) {
    updateNode(node.get());
  }
}

void UpdateModule::updateNode(Node* node) {
  for (auto& component : node->components()) {
    if (component->enabled()) {
      component->update();
    }
  }

  for (auto& child : node->children()) {
    if (child->active()) {
      updateNode(child);
    }
  }
}

}
