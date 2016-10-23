#ifndef __BELLUM_MESH_RENDERER_H__
#define __BELLUM_MESH_RENDERER_H__

#include "../common.h"
#include "renderer.h"
#include "mesh_filter.h"
#include "../resources/mesh.h"

namespace bellum {

class MeshRenderer : public Renderer {
public:
  DEFINE_EXCEPTION(NoMeshFilterException, "No 'MeshFilter' on this node");

  inline void onAdd() override {
    mesh_filter_ = node_->getComponent<MeshFilter>();
    if (mesh_filter_ == nullptr) {
      throw NoMeshFilterException{};
    }
  }

  inline void render() override final {
    mesh_filter_->mesh()->render();
  }

private:
  MeshFilter* mesh_filter_;
};

}

#endif
