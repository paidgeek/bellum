#ifndef BELLUM_SCENE_H
#define BELLUM_SCENE_H

#include "common/common.h"
#include "node.h"

namespace bellum {

class Scene {
public:
  virtual void make() = 0;
  void update();
  void render();

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
private:
  std::vector<std::unique_ptr<Node>> nodes_;
};

}

#endif
