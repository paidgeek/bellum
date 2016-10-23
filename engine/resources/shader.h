#ifndef __BELLUM_SHADER_H__
#define __BELLUM_SHADER_H__

#include "../common.h"
#include <unordered_map>
#include "../color.h"
#include "../math/matrix4.h"
#include "../math/vector2.h"
#include "../math/vector3.h"
#include "../math/vector4.h"
#include "resource.h"

namespace bellum {

class Shader : public Resource {
  friend class ResourceLoader;
  friend class RenderModule;

public:
  DEFINE_EXCEPTION(CreateException, "Failed to create a new shader program");
  DEFINE_EXCEPTION(CompilationException, "Failed to compile shader");
  DEFINE_EXCEPTION(LinkException, "Failed to link shader");
  DEFINE_EXCEPTION(BindUniformException, "Could not bind uniform");

protected:
  void dispose() override;

private:
  struct Uniform {
    std::string name;
    int32 location;
  };
  using UniformMap = std::unordered_map<std::string, Uniform>;

  Shader(uint8 pass, uint32 program, UniformMap uniforms);

  void setUniform(const std::string& name, float value);
  void setUniform(const std::string& name, const std::vector<float>& value);
  void setUniform(const std::string& name, int32 value);
  void setUniform(const std::string& name, const Matrix4& value);
  void setUniform(const std::string& name, const Vector2& value);
  void setUniform(const std::string& name, const Vector3& value);
  void setUniform(const std::string& name, const Vector4& value);
  void setUniform(const std::string& name, const Color& value);
  void setUniform(const std::string& name, bool value);

  void bind();
  void release();

  uint8 pass_;
  uint32 program_;
  UniformMap uniforms_;
};

}

#endif
