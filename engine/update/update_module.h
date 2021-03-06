#ifndef __BELLUM_LOGIC_MODULE_H__
#define __BELLUM_LOGIC_MODULE_H__

#include "../common.h"
#include "../module.h"

namespace bellum {

class Node;

class UpdateModule : public Module {
public:
  UpdateModule(){}

  void onStart(Scene* scene) override;
  void update() override;

private:
  void updateNode(Node* node);
};

}

#endif
