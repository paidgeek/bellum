#include "shader.h"
#include <GL/glew.h>

namespace bellum {

Shader::Shader(uint8 pass, uint32 program, UniformMap uniforms)
  : pass_(pass), program_(program), uniforms_(uniforms) {}

void Shader::setUniform(const std::string& name, float value) {
  int32 location = uniforms_[name].location;
  glUniform1f(location, value);
}

void Shader::setUniform(const std::string& name, const std::vector<float>& value) {
  int32 location = uniforms_[name].location;
  glUniform1fv(location, value.size(), value.data());
}

void Shader::setUniform(const std::string& name, int32 value) {
  int32 location = uniforms_[name].location;
  glUniform1i(location, value);
}

void Shader::setUniform(const std::string& name, const Matrix4& value) {
  int32 location = uniforms_[name].location;
  glUniformMatrix4fv(location, 16, GL_FALSE, value.data);
}

void Shader::setUniform(const std::string& name, const Vector2& value) {
  int32 location = uniforms_[name].location;
  glUniform2f(location, value.x, value.y);
}

void Shader::setUniform(const std::string& name, const Vector3& value) {
  int32 location = uniforms_[name].location;
  glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const Vector4& value) {
  int32 location = uniforms_[name].location;
  glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string& name, const Color& value) {
  int32 location = uniforms_[name].location;
  glUniform4f(location, value.r, value.g, value.b, value.a);
}

void Shader::setUniform(const std::string& name, bool value) {
  int32 location = uniforms_[name].location;
  glUniform1i(location, value);
}

void Shader::bind() {
  glUseProgram(program_);
}

void Shader::release() {
  glUseProgram(0);
}

void Shader::dispose() {
  glDeleteProgram(program_);
}

}
