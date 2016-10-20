#ifndef __BELLUM_LOGIC_MODULE_H__
#define __BELLUM_LOGIC_MODULE_H__

#include "common/common.h"
#include "../module.h"

namespace bellum {

class Node;

class UpdateModule : public Module {
public:
  UpdateModule(){}

  void onEnterScene(Scene* scene) override;
  void update() override;

private:
  void updateNode(Node* node);
};

}

#endif
