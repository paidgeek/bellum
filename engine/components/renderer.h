#ifndef __BELLUM_RENDERER_H__
#define __BELLUM_RENDERER_H__

#include "../common.h"
#include "../component.h"
#include "../resources/material.h"

namespace bellum {

class Renderer : public Component {
  friend class RenderModule;

public:
  const Material& material() const {
    return material_;
  }

  void setMaterial(const Material& material);

protected:
  virtual void render() = 0;

  Material material_;
};

}

#endif
