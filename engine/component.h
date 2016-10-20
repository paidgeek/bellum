#ifndef __BELLUM_COMPONENT_H__
#define __BELLUM_COMPONENT_H__

#include "common/common.h"

namespace bellum {

class Node;

class Component {
  friend class Node;
  friend class Scene;

public:
  Component() {}

  inline bool enabled() const {
    return enabled_;
  }

  inline Node* node() {
    return node_;
  }

protected:
  virtual void onAdd() {};
  virtual void onRemove() {};
  virtual void onEnable() {};
  virtual void onDisable() {};
  virtual void update() {};

private:
  Node* node_;
  bool enabled_;
};

}

#endif
