#ifndef __BELLUM_COMPONENT_H__
#define __BELLUM_COMPONENT_H__

#include "common.h"

namespace bellum {

class Node;

class Component {
  friend class Scene;
  friend class Node;

public:
  Component()
    : enabled_(true) {}

  inline bool enabled() const {
    return enabled_;
  }

  inline Node* node() const {
    return node_;
  }

  virtual void onAdd() {};
  virtual void onRemove() {};
  virtual void onEnable() {};
  virtual void onDisable() {};
  virtual void update() {};

protected:
  Node* node_;
  bool enabled_;
};

}

#endif
