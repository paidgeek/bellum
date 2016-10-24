#include <fstream>
#include <sstream>
#include "resource_loader.h"
#include "resource.h"
#include "shader.h"
#include "mesh.h"
#include "../application.h"

#include <GL/glew.h>

namespace bellum {

std::vector<std::unique_ptr<Resource>> ResourceLoader::resources_;
std::string ResourceLoader::kParentDirectory  = "assets";

std::string ResourceLoader::getAssetPath(const std::string& asset) {
  if(asset[0] == '/') {
    return kParentDirectory + asset;
  } else {
    return kParentDirectory + "/" + asset;
  }
}

Shader* ResourceLoader::loadShader(const std::string& vertexShaderAsset,
                                   const std::string& fragmentShaderAsset,
                                   const BindingInfo& bindingInfo,
                                   const std::vector<std::string>& uniformNames) {
  Shader::UniformMap uniforms;
  for (auto& name : uniformNames) {
    uniforms.insert(std::make_pair(name, Shader::Uniform{name, -1}));
  }

  uint32 program = glCreateProgram();
  if (program == 0) {
    throw Shader::CreateException{};
  }

  std::string vs = loadTextAsset(vertexShaderAsset);
  std::string fs = loadTextAsset(fragmentShaderAsset);

  compileShader(vs, GL_VERTEX_SHADER, program);
  compileShader(fs, GL_FRAGMENT_SHADER, program);

  // bind attributes
  for (auto& ap : bindingInfo.attribute_pointers) {
    glBindAttribLocation(program, ap.location, AttributeKindUtil::getName(ap.kind));
    GL_CHECK();
  }

  linkShaderProgram(program);

  glUseProgram(program);
  // bind uniforms
  for (auto& kv : uniforms) {
    int32 location = glGetUniformLocation(program, kv.first.c_str());
    if (location == -1) {
      throw Shader::BindUniformException{Formatter::str("Could not bind uniform '", kv.first, "'")};
    }
    kv.second.location = location;
  }
  glUseProgram(0);

  Application::instance()->logger()->info("Loaded shader vs: '",
                                             vertexShaderAsset, "' fs: '",
                                             fragmentShaderAsset, "'");

  Shader* shader = new Shader{0, program, uniforms};
  resources_.push_back(std::unique_ptr<Shader>{shader});
  return shader;
}

void ResourceLoader::compileShader(const std::string& source, uint32 type, uint32 program) {
  uint32 shader = glCreateShader(type);

  if (shader == 0) {
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

  if (vaoId == 0 || vboId == 0 || iboId == 0) {
    throw MakeMeshException{};
  }

  resources_.emplace_back(new Mesh{bindingInfo, vaoId, vboId, iboId});
  return dynamic_cast<Mesh*>(resources_.back().get());
}

std::string ResourceLoader::loadTextAsset(const std::string& asset) {
  std::string path = getAssetPath(asset);
  std::ifstream in{path, std::ios::binary};
  if (!in.is_open()) {
    throw AssetNotFoundException{Formatter::str("Asset '", path, "' not found")};
  }

  std::stringstream ss;
  ss << in.rdbuf();

  Application::instance()->logger()->info("Loaded text asset '", path, "'");

  in.close();

  return ss.str();
}

void ResourceLoader::disposeAll() {
  for (auto& resource : resources_) {
    resource->dispose();
  }
  resources_.clear();

  Application::instance()->logger()->info("Released all resources");
}

}
