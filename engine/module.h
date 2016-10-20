#ifndef __BELLUM_MODULE_H__
#define __BELLUM_MODULE_H__

#include "common/common.h"

namespace bellum {

class Scene;

class Module {
public:
  Module() {}

  virtual void onEnterScene(Scene* scene) = 0;
  virtual void update() {};
  virtual void render() {};

protected:
  Scene* scene_;
};

}

#endif
