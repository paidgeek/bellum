#ifndef BELLUM_RENDER_MODULE_H
#define BELLUM_RENDER_MODULE_H

#include "../common.h"
#include "../module.h"
#include "../math/matrix4.h"

namespace bellum {

class Component;
class Renderer;

class RenderModule : public Module {
public:
  DEFINE_EXCEPTION(IllegalRenderersState, "Illegal renderers state");

  RenderModule() {}

  void onStart(Scene* scene) override;
  void render() override;
  void consolidate();

  void addRenderer(Renderer* renderer);

private:
  struct RenderState {
    Renderer* renderer;
    Matrix4 projection;
    Matrix4 view_projection;

    void clear() {
      renderer = nullptr;
    }
  } render_state;

  void ambientPass();

  std::vector<Renderer*> renderers_;
};

}

#endif
