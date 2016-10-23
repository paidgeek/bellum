#ifndef __BELLUM_GAME_OBJECT_H__
#define __BELLUM_GAME_OBJECT_H__

#include "common.h"
#include "transform.h"
#include "component.h"

namespace bellum {

class Node {
  friend class Scene;
  friend class SceneManager;

public:
  Node(int32 id)
    : id_(id), active_(true) {}

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

  inline const std::vector<std::unique_ptr<Component>>& components() const {
    return components_;
  }

  template<typename T>
  inline T* addComponent() {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    std::unique_ptr<Component> component = std::make_unique<T>();
    Component* c = component.get();
    components_.push_back(std::move(component));

    c->node_ = this;
    c->onAdd();

    notifyOnAddComponent(c);

    return dynamic_cast<T*>(c);
  }

  template<typename T>
  inline T* getComponent() {
    for (const auto& component : components_) {
      T* ptr = dynamic_cast<T*>(component.get());
      if (ptr != nullptr) {
        return ptr;
      }
    }

    return nullptr;
  }

  inline const std::vector<Node*>& children() const {
    return children_;
  }

  static Node* make(Node* parent = nullptr);

private:
  void notifyOnAddComponent(Component* component) const;

  int32 id_;
  Transform transform_;
  std::string tag_;
  bool active_;
  std::vector<std::unique_ptr<Component>> components_;
  std::vector<Node*> children_;
};

}

#endif
