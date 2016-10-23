#ifndef __BELLUM_MATERIAL_H__
#define __BELLUM_MATERIAL_H__

#include "../common.h"

namespace bellum {

struct Shader;

struct Material {
  Shader* shader;

  inline Material();
  inline Material(Shader* shader);
  inline Material(const Material& other);
  inline Material& operator=(const Material& other);
};

Material::Material() {}

Material::Material(Shader* shader)
  : shader(shader) {}

Material::Material(const Material& other)
  : shader(other.shader) {}

Material& Material::operator=(const Material& other) {
  shader = other.shader;
}

}

#endif
