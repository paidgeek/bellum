#ifndef BELLUM_SCENE_H
#define BELLUM_SCENE_H

#include "common/common.h"

namespace bellum {

class Module;

class Scene {
  friend class Application;

public:
  virtual void onStart() = 0;

private:
  std::vector<std::unique_ptr<Module>> modules_;

  template<typename T>
  void registerModule() {
    modules_.emplace_back(new T{});
  }
};

}

#endif
