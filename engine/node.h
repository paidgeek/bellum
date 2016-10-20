#ifndef __BELLUM_GAME_OBJECT_H__
#define __BELLUM_GAME_OBJECT_H__

#include "common/common.h"
#include "transform.h"
#include "component.h"

namespace bellum {

class Node {
  friend class Component;
  friend class Scene;

public:
  Node(int32 id)
    : id_(id) {}

  inline int32 id() const {
    return id_;
  }

  inline Transform& transform() {
    return transform_;
  }

  inline const Transform& transform() const {
    return transform_;
  }

  inline const std::string& tag() const {
    return tag_;
  }

  inline void setTag(std::string tag) {
    tag_ = tag;
  }

  inline bool active() const {
    return active_;
  }

private:
  inline const std::vector<std::unique_ptr<Component>>& components() const {
    return components_;
  }

  inline void addComponent(std::unique_ptr<Component> component) {
    components_.push_back(std::move(component));
  }

  int32 id_;
  Transform transform_;
  std::string tag_;
  bool active_;
  std::vector<std::unique_ptr<Component>> components_;
  std::vector<Node*> children_;
};

}

#endif
