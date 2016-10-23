#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include "resource_loader.h"
#include "resource.h"
#include "shader.h"
#include "mesh.h"
#include "../application.h"

namespace bellum {

std::vector<std::unique_ptr<Resource>> ResourceLoader::resources_;

Shader* ResourceLoader::loadShader(const std::string& vertexShaderAsset,
                                   const std::string& fragmentShaderAsset,
                                   const BindingInfo& bindingInfo,
                                   const std::vector<std::string>& uniformNames) {
  Shader::UniformMap uniforms;
  for (auto& name : uniformNames) {
    uniforms[name] = Shader::Uniform{name, -1};
  }

  uint32 program = glCreateProgram();
  if (program == 0) {
    throw Shader::CreateException{};
  }

  std::string vs = LoadTextAsset(vertexShaderAsset);
  std::string fs = LoadTextAsset(fragmentShaderAsset);

  compileShader(vs, GL_VERTEX_SHADER, program);
  compileShader(fs, GL_FRAGMENT_SHADER, program);

  // bind attributes
  for (auto& ap : bindingInfo.attribute_pointers) {
    glBindAttribLocation(program, ap.location, AttributeKindUtil::getName(ap.kind));
  }

  linkShaderProgram(program);

  // bind uniforms
  for (auto& kv : uniforms) {
    int32 location = glGetUniformLocation(program, kv.first.c_str());
    if (location == -1) {
      throw Shader::BindUniformException{};
    }
    kv.second.location = location;
  }

  Application::getInstance()->logger()->info("Loaded shader vs: '",
                                             vertexShaderAsset, "' fs: '",
                                             fragmentShaderAsset, "'");

  resources_.push_back(std::unique_ptr<Shader>{new Shader{0, program, uniforms}});
  return dynamic_cast<Shader*>(resources_.back().get());
}

void ResourceLoader::compileShader(const std::string& source, uint32 type, uint32 program) {
  uint32 shader = glCreateShader(type);

  if (shader == 0) {
    glDeleteProgram(program);
    throw Shader::CompilationException{};
  }

  const char* sources[1];
  sources[0] = source.c_str();
  int32 lengths[1];
  lengths[0] = source.size();
  glShaderSource(shader, 1, sources, lengths);
  glCompileShader(shader);

  int32 success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info[1024];
    glGetShaderInfoLog(shader, sizeof(info), nullptr, info);
    std::cerr << info << std::endl;

    glDeleteProgram(program);
    throw Shader::CompilationException{};
  }

  glAttachShader(program, shader);
}

void ResourceLoader::linkShaderProgram(uint32 program) {
  glLinkProgram(program);
  int32 success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (success == GL_FALSE) {
    char info[1024];
    glGetProgramInfoLog(program, sizeof(info), nullptr, info);
    std::cerr << info << std::endl;

    glDeleteProgram(program);
    throw Shader::LinkException{};
  }

  glValidateProgram(program);
  glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
  if (success == GL_FALSE) {
    char info[1024];
    glGetProgramInfoLog(program, sizeof(info), nullptr, info);
    std::cerr << info << std::endl;

    glDeleteProgram(program);
    throw Shader::LinkException{};
  }
}

Mesh* ResourceLoader::makeEmptyMesh(const BindingInfo& bindingInfo) {
  uint32 vaoId, vboId, iboId;
  glGenVertexArrays(1, &vaoId);
  glGenBuffers(1, &vboId);
  glGenBuffers(1, &iboId);

  if(vaoId == 0 || vboId == 0 || iboId == 0) {
    throw MakeMeshException{};
  }

  resources_.push_back(std::unique_ptr<Mesh>{new Mesh{bindingInfo, vaoId, vboId, iboId}});
  return dynamic_cast<Mesh*>(resources_.back().get());
}

std::string ResourceLoader::LoadTextAsset(const std::string& asset) {
  std::ifstream in{asset};
  std::stringstream ss;
  ss << in.rdbuf();

  Application::getInstance()->logger()->info("Loaded text asset '", asset, "'");

  return ss.str();
}

void ResourceLoader::disposeAll() {
  for (auto& resource : resources_) {
    resource->dispose();
  }
  resources_.clear();

  Application::getInstance()->logger()->info("Disposed all resources");
}

}
