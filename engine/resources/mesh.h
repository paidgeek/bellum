#ifndef __BELLUM_MESH_H__
#define __BELLUM_MESH_H__

#include "../common.h"
#include "resource.h"

namespace bellum {

class Mesh : public Resource {
  friend class ResourceLoader;
  friend class RenderModule;

public:
  Mesh();

  void build();
private:
  void render();

  int vao_id;
  int vbo_id;
  int ibo_id;
};

}

#endif
