#ifndef __BELLUM_MODULE_H__
#define __BELLUM_MODULE_H__

namespace bellum {

class Scene;

class Module {
public:
  Module(Scene* scene)
    : scene_(scene) {}

  virtual void onStart() = 0;
  virtual void update() = 0;
  virtual void render() = 0;
protected:
  Scene* scene_;
};

}

#endif
