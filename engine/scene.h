#ifndef BELLUM_SCENE_H
#define BELLUM_SCENE_H

#include "common.h"
#include "node.h"
#include "component.h"

namespace bellum {

class Scene {
public:
  virtual void make() = 0;

  inline const std::vector<std::unique_ptr<Node>>& nodes() const {
    return nodes_;
  }

  Node* makeNode() {
    static int idCounter = 0;
    nodes_.emplace_back(new Node{++idCounter});
    return (*nodes_.end()).get();
  }

  template<typename T>
  T* makeComponent(Node* node) {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    std::unique_ptr<T> c{std::make_unique<T>()};
    c->onAdd();
    node->addComponent(std::move(c));
  }

  inline void registerOnAddComponent(std::function<void(Component*)> callback) {
    on_add_component.push_back(callback);
  }

  inline void registerOnRemoveComponent(std::function<void(Component*)> callback) {
    on_remove_component.push_back(callback);
  }

  inline void registerOnMakeNode(std::function<void(Node*)> callback) {
    on_make_node.push_back(callback);
  }

  inline void registerOnDestroyNode(std::function<void(Node*)> callback) {
    on_destroy_node.push_back(callback);
  }

private:
  void notifyAddComponent(Component* component);
  void notifyRemoveComponent(Component* component);
  void notifyMakeNode(Node* node);
  void notifyDestroyNode(Node* node);
  void clearObservers();

  std::vector<std::unique_ptr<Node>> nodes_;

  std::vector<std::function<void(Component*)>> on_add_component;
  std::vector<std::function<void(Component*)>> on_remove_component;
  std::vector<std::function<void(Node*)>> on_make_node;
  std::vector<std::function<void(Node*)>> on_destroy_node;
};

}

#endif
