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

  DEFINE_EXCEPTION(AssetNotFoundException, "Asset not found");
  DEFINE_EXCEPTION(MakeMeshException, "Failed to create a new mesh");

public:
  static Shader* loadShader(const std::string& vertexShaderAsset,
                                            const std::string& fragmentShaderAsset,
                                            const BindingInfo& bindingInfo,
                                            const std::vector<std::string>& uniformNames);
  static Mesh* makeEmptyMesh(const BindingInfo& bindingInfo);
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
