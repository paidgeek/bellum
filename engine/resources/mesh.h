#ifndef __BELLUM_MESH_H__
#define __BELLUM_MESH_H__

#include "../common.h"
#include "resource.h"
#include "../math/bounds.h"
#include "../math/vector3.h"
#include "../math/vector2.h"
#include "color.h"
#include "binding_info.h"

namespace bellum {

class Mesh : public Resource {
  friend class ResourceLoader;
  friend class MeshFactory;
  friend class MeshRenderer;

  DEFINE_EXCEPTION(NotReadableException, "Mesh data is not readable");
  DEFINE_EXCEPTION(InvalidData, "Invalid data");

public:
  inline const Bounds& bounds() const;
  inline const std::vector<Color>& colors() const;
  inline void setColors(const std::vector<Color>& colors);
  template<uint32 count>
  inline void setColors(std::array<float, count> colors);
  inline const std::vector<Vector3>& normals() const;
  inline void setNormals(const std::vector<Vector3>& normals);
  template<uint32 count>
  inline void setNormals(std::array<float, count> normals);
  inline const std::vector<Vector3>& vertices() const;
  inline void setVertices(const std::vector<Vector3>& vertices);
  template<uint32 count>
  inline void setVertices(std::array<float, count> vertices);
  inline const std::vector<Vector2>& uv() const;
  inline void setUv(const std::vector<Vector2>& uv);
  inline const std::vector<uint32>& triangles() const;
  inline void setTriangles(const std::vector<uint32>& triangles);
  inline bool readable() const;

  void clear();
  void markDynamic();
  void recalculateBounds();
  void recalculateNormals();
  void uploadMeshData(bool markNoLongerReadable = true);

protected:
  void dispose() override;

private:
  Mesh(BindingInfo bindingInfo, uint32 vaoId, uint32 vboId, uint32 iboId);

  void render();

  Bounds bounds_;
  BindingInfo binding_info_;
  bool dynamic_;
  std::vector<Color> colors_;
  std::vector<Vector3> normals_;
  std::vector<Vector3> vertices_;
  std::vector<Vector2> uv_;
  std::vector<uint32> triangles_;
  uint32 triangle_count_;
  bool readable_;
  uint32 vao_id_;
  uint32 vbo_id_;
  uint32 ibo_id_;
};

inline const Bounds& Mesh::bounds() const {
  return bounds_;
}

inline const std::vector<Color>& Mesh::colors() const {
  if (!readable_) {
    throw NotReadableException{};
  }
  return colors_;
}

inline void Mesh::setColors(const std::vector<Color>& colors) {
  colors_ = colors;
}

template<uint32 count>
void Mesh::setColors(std::array<float, count> colors) {
  colors_.clear();
  for (uint32 i = 0; i < count; i += 4) {
    colors_.push_back(Color{&colors[i]});
  }
}

inline const std::vector<Vector3>& Mesh::normals() const {
  if (!readable_) {
    throw NotReadableException{};
  }
  return normals_;
}

inline void Mesh::setNormals(const std::vector<Vector3>& normals) {
  normals_ = normals;
}

template<uint32 count>
void Mesh::setNormals(std::array<float, count> normals) {
  normals_.clear();
  for (uint32 i = 0; i < count; i += 3) {
    normals_.push_back(Vector3{&normals[i]});
  }
}

inline const std::vector<Vector3>& Mesh::vertices() const {
  if (!readable_) {
    throw NotReadableException{};
  }
  return vertices_;
}

inline void Mesh::setVertices(const std::vector<Vector3>& vertices) {
  vertices_ = vertices;
}

template<uint32 count>
void Mesh::setVertices(std::array<float, count> vertices) {
  vertices_.clear();
  for (uint32 i = 0; i < count; i += 3) {
    vertices_.push_back(Vector3{&vertices[i]});
  }
}

inline const std::vector<Vector2>& Mesh::uv() const {
  if (!readable_) {
    throw NotReadableException{};
  }
  return uv_;
}

inline void Mesh::setUv(const std::vector<Vector2>& uv) {
  uv_ = uv;
}

inline const std::vector<uint32>& Mesh::triangles() const {
  if (!readable_) {
    throw NotReadableException{};
  }
  return triangles_;
}

inline void Mesh::setTriangles(const std::vector<uint32>& triangles) {
  triangle_count_ = triangles.size();
  triangles_ = triangles;
}

inline bool Mesh::readable() const {
  return readable_;
}

}

#endif
