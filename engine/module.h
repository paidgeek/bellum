#ifndef __BELLUM_MODULE_H__
#define __BELLUM_MODULE_H__

#include "common/common.h"

namespace bellum {

class Scene;

class Module {
friend class Scene;

protected:
  Module(Scene* scene)
  :scene_(scene){}

  virtual void onCreate() {};
  virtual void update() {};
  virtual void render() {};

  Scene* scene_;
};

}

#endif
