#ifndef BELLUM_SCENE_H
#define BELLUM_SCENE_H

#include "common/common.h"

namespace bellum {

class Scene {
public:
  virtual void make() = 0;

  void update();
  void render();
};

}

#endif
