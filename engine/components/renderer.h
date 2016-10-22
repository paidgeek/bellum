#ifndef __BELLUM_RENDERER_H__
#define __BELLUM_RENDERER_H__

#include "../common.h"
#include "../component.h"

namespace bellum {

class Renderer : public Component {
public:
  virtual void render() = 0;
};

}

#endif
