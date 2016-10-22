#ifndef __BELLUM_RESOURCE_LOADER_H__
#define __BELLUM_RESOURCE_LOADER_H__

#include <unordered_map>
#include "../common.h"
#include "binding_info.h"

namespace bellum {

class Resource;
class Shader;
class Mesh;

class ResourceLoader {
  friend class StandaloneApplication;

public:
  static Shader* loadShader(const std::string& vertexShaderAsset,
                                            const std::string& fragmentShaderAsset,
                                            BindingInfo bindingInfo,
                                            std::vector<std::string> uniformNames);
  static std::string LoadTextAsset(const std::string& asset);

private:
  ResourceLoader() {};

  static void compileShader(const std::string& source, uint32 type, uint32 program);
  static void linkShaderProgram(uint32 program);
  static void disposeAll();

  static std::vector<std::unique_ptr<Resource>> resources_;
};

}

#endif
