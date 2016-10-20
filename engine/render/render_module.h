#ifndef BELLUM_RENDER_MODULE_H
#define BELLUM_RENDER_MODULE_H

#include "../common/common.h"
#include "../module.h"
#include "renderer.h"

namespace bellum {

class RenderModule : public Module {
public:
  RenderModule() {}

  template<typename T>
  void setRenderer() {
    renderer_ = std::make_unique<T>();
  }

  void onEnterScene(Scene* scene) override;
  void render() override;

private:
  std::unique_ptr<Renderer> renderer_;
};

}

#endif
