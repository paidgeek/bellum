#ifndef __BELLUM_MESHFACTORY_H__
#define __BELLUM_MESHFACTORY_H__

#include "../common.h"

namespace bellum {

class Mesh;
class BindingInfo;

class MeshFactory {
public:
  static Mesh* makeCube(const BindingInfo& bindingInfo, float width, float height, float depth);

};

}

#endif
