#include "scene.h"

namespace bellum {

inline void Scene::notifyAddComponent(Component* component) {
  for (auto& observer : on_add_component) {
    observer(component);
  }
}

inline void Scene::notifyRemoveComponent(Component* component) {
  for (auto& observer : on_remove_component) {
    observer(component);
  }
}

inline void Scene::notifyMakeNode(Node* node) {
  for (auto& observer : on_make_node) {
    observer(node);
  }
}

inline void Scene::notifyDestroyNode(Node* node) {
  for (auto& observer : on_destroy_node) {
    observer(node);
  }
}

void Scene::clearObservers() {
  on_add_component.clear();
  on_remove_component.clear();
  on_make_node.clear();
  on_destroy_node.clear();
}

}
