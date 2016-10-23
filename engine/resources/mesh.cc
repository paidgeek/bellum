#include "mesh.h"
#include <GL/glew.h>
#include <valarray>

#include "../color.h"
#include "../math/vector2.h"

namespace bellum {

Mesh::Mesh(BindingInfo bindingInfo, uint32 vaoId, uint32 vboId, uint32 iboId)
  : binding_info_(bindingInfo),
    vao_id_(vaoId),
    vbo_id_(vboId),
    ibo_id_(iboId),
    readable_(true),
    dynamic_(false) {}

void Mesh::clear() {
  colors_.clear();
  vertices_.clear();
  triangles_.clear();
  uv_.clear();
}

void Mesh::markDynamic() {
  dynamic_ = true;
}

void Mesh::recalculateBounds() {
  if (!readable_) {
    throw NotReadableException{};
  }

  Vector3 v = vertices_[0];
  Vector3 min = v, max = v;

  for (int i = 1; i < vertices_.size(); i++) {
    v = vertices_[i];
    min = Vector3::min(min, v);
    max = Vector3::max(max, v);
  }

  bounds_.setMinMax(min, max);
}

void Mesh::recalculateNormals() {
  normals_.clear();
  normals_.reserve(vertices_.size());
  for (uint32 i = 0; i < vertices_.size(); i++) {
    normals_.emplace_back();
  }

  for (uint32 i = 0; i < triangles_.size(); i += 3) {
    uint32 i1 = triangles_[i];
    uint32 i2 = triangles_[i + 1];
    uint32 i3 = triangles_[i + 2];

    Vector3 v1 = vertices_[i2] - vertices_[i1];
    Vector3 v2 = vertices_[i3] - vertices_[i1];

    Vector3 normal = Vector3::cross(v1, v2).normalized();

    normals_[i1] = (normals_[i1] + normal).normalized();
    normals_[i2] = (normals_[i2] + normal).normalized();
    normals_[i3] = (normals_[i3] + normal).normalized();
    normals_[i1] = (normals_[i1] + normal).normalized();
  }
}

void Mesh::uploadMeshData(bool markNoLongerReadable) {
  readable_ = markNoLongerReadable;
  triangle_count_ = triangles_.size();

  // create vertex buffer
  std::valarray<float> vb(vertices_.size() * binding_info_.size);
  uint32 j = 0;

  Vector3 v, n;
  Vector2 uv;
  Color c;
  for (uint32 i = 0; i < vertices_.size(); i++) {
    for (auto& ap : binding_info_.attribute_pointers) {
      switch (ap.kind) {
        case AttributeKind::POSITION:
          v = vertices_[i];
          vb[j++] = v.x;
          vb[j++] = v.y;
          vb[j++] = v.z;
          break;
        case AttributeKind::TEXTURE_COORDINATE:
          uv = uv_[i];
          vb[j++] = uv.x;
          vb[j++] = uv.y;
          break;
        case AttributeKind::NORMAL:
          n = normals_[i];
          vb[j++] = n.x;
          vb[j++] = n.y;
          vb[j++] = n.z;
          break;
        case AttributeKind::COLOR:
          c = colors_[i];
          vb[j++] = c.r;
          vb[j++] = c.g;
          vb[j++] = c.b;
          vb[j++] = c.a;
          break;
      }
    }
  }

  // upload buffers
  uint32 drawType = dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
  glBindVertexArray(vao_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
  glBufferData(GL_ARRAY_BUFFER, vb.size(), std::begin(vb), drawType);

  uint32 offset = 0;
  for (const auto& ap : binding_info_.attribute_pointers) {
    uint32 size = AttributeKindUtil::getSize(ap.kind);
    glVertexAttribPointer(ap.location, size, GL_FLOAT, GL_FALSE, binding_info_.size,
                          (const GLvoid*) offset);
    offset += size * sizeof(float);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles_.size(), triangles_.data(), drawType);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  if (markNoLongerReadable) {
    clear();
    readable_ = false;
  } else {
    readable_ = true;
  }
}

void Mesh::render() {
  glBindVertexArray(vao_id_);

  for (const auto& ap : binding_info_.attribute_pointers) {
    glEnableVertexAttribArray(ap.location);
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id_);
  glDrawElements(GL_TRIANGLES, triangle_count_, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  for (const auto& ap : binding_info_.attribute_pointers) {
    glDisableVertexAttribArray(ap.location);
  }

  glBindVertexArray(0);
}

void Mesh::dispose() {
  glDeleteVertexArrays(1, &vao_id_);
  glDeleteBuffers(1, &vbo_id_);
  glDeleteBuffers(1, &ibo_id_);
}

}
