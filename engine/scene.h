#ifndef BELLUM_SCENE_H
#define BELLUM_SCENE_H

#include "common.h"
#include "node.h"
#include "component.h"

namespace bellum {

class Scene {
  friend class Node;

public:
  Scene()
    : root_(Node{1}) {}

  virtual void make() = 0;

  inline const std::vector<std::unique_ptr<Node>>& nodes() const {
    return nodes_;
  }

private:
  Node* makeNode(Node* parent = nullptr) {
    if (parent == nullptr) {
      parent = &root_;
    }

    static int idCounter = 1;
    nodes_.emplace_back(new Node{++idCounter});
    Node* node = nodes_.back().get();

    parent->children_.push_back(node);

    return node;
  }

  Node root_;
  std::vector<std::unique_ptr<Node>> nodes_;
};

}

#endif
