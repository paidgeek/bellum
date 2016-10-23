#ifndef __BELLUM_MESH_H__
#define __BELLUM_MESH_H__

#include "../common.h"
#include "resource.h"
#include "../math/bounds.h"
#include "binding_info.h"

namespace bellum {

struct Color;
struct Vector3;
struct Vector2;

class Mesh : public Resource {
  friend class ResourceLoader;
  friend class MeshRenderer;

  DEFINE_EXCEPTION(NotReadableException, "Mesh data is not readable");

public:
  inline const Bounds& bounds() const;
  inline const std::vector<Color>& colors() const;
  inline void setColors(const std::vector<Color>& colors);
  inline const std::vector<Vector3>& normals() const;
  inline void setNormals(const std::vector<Vector3>& normals);
  inline const std::vector<Vector3>& vertices() const;
  inline void setVertices(const std::vector<Vector3>& vertices);
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

inline const std::vector<Vector3>& Mesh::normals() const {
  if (!readable_) {
    throw NotReadableException{};
  }
  return normals_;
}

inline void Mesh::setNormals(const std::vector<Vector3>& normals) {
  normals_ = normals;
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
  triangles_ = triangles;
}

inline bool Mesh::readable() const {
  return readable_;
}

}

#endif
