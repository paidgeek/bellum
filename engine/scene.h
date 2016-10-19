#ifndef BELLUM_SCENE_H
#define BELLUM_SCENE_H

#include "common/common.h"
#include "game_object.h"

namespace bellum {

class Scene {
public:
  virtual void make() = 0;

  void update();
  void render();

private:
  GameObject root_;

};

}

#endif
