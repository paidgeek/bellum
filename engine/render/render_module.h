#ifndef BELLUM_RENDER_MODULE_H
#define BELLUM_RENDER_MODULE_H

#include "../common/common.h"
#include "renderer.h"

namespace bellum {

class RenderModule {
public:
  template<typename T>
  void setRenderer() {
    renderer_ = std::make_unique<T>();
  }
private:
  std::unique_ptr<Renderer> renderer_;
};

}

#endif
