#include "node.h"
#include "scene_manager.h"
#include "scene.h"
#include "components/renderer.h"
#include "render/render_module.h"
#include "application.h"

namespace bellum {

Node* Node::make(Node* parent) {
  return SceneManager::currentScene()->makeNode(parent);
}

void Node::notifyOnAddComponent(Component* component) const {
  Renderer* renderer = dynamic_cast<Renderer*>(component);

  if (renderer != nullptr) {
    Application::instance()->render_module_->addRenderer(renderer);
  }
}

}
