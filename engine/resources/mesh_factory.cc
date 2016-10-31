#include "mesh_factory.h"
#include "mesh.h"
#include "../resources/binding_info.h"
#include <GL/glew.h>
#include "resource_loader.h"
#include "binding_info.h"

namespace bellum {



Mesh* MeshFactory::makeCube(const BindingInfo& bindingInfo,
                            float width,
                            float height,
                            float depth) {
  std::vector<float> vertData{
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f
  };

  for(uint32 i = 0; i < vertData.size(); i += 3) {
    vertData[i] *= width / 2.0f;
    vertData[i + 1] *= height / 2.0f;
    vertData[i + 2] *= depth / 2.0f;
  }

  std::vector<Vector3> vertices;
  std::vector<uint32> triangles;
  vertices.reserve(vertData.size() / 3);
  triangles.reserve(vertData.size() / 3);

  for(uint32 i = 0; i < vertData.size() / 3; i++) {
    vertices.push_back(Vector3{vertData[i*3], vertData[i*3 + 1], vertData[i*3 + 2]});
    triangles.push_back(i);
  }

  Mesh* cube = ResourceLoader::makeEmptyMesh(bindingInfo);
  cube->setVertices(vertices);
  cube->setTriangles(triangles);

  if(bindingInfo.has(AttributeKind::COLOR)) {
    std::vector<Color> colors;
    colors.reserve(vertices.size());

    for(uint32 i = 0; i < vertices.size(); i++) {
      colors.push_back(Color::white());
    }

    cube->setColors(colors);
  }

  return cube;
}

}
