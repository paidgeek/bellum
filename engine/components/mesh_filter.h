#ifndef __BELLUM_MESH_FILTER_H__
#define __BELLUM_MESH_FILTER_H__

#include "../common.h"
#include "../component.h"

namespace bellum {

class Mesh;

class MeshFilter : public Component {
public:
  Mesh* mesh() const {
    return mesh_;
  }

  void setMesh(Mesh* mesh) {
    mesh_ = mesh;
  }

private:
  Mesh* mesh_;
};

}

#endif
