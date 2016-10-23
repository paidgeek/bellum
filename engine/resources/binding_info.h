#ifndef __BELLUM_BINDING_INFO_H__
#define __BELLUM_BINDING_INFO_H__

#include "../common.h"
#include "attribute.h"

namespace bellum {

struct BindingInfo {
  std::vector<AttributePointer> attribute_pointers;
  uint32 size;

  inline BindingInfo(std::vector<AttributeKind> attributeKinds) {
    attribute_pointers.clear();
    size = 0;

    for (auto& ak : attributeKinds) {
      attribute_pointers.emplace_back(ak, attribute_pointers.size());
      size += AttributeKindUtil::getSize(ak);
    }
  }

  inline BindingInfo(std::vector<AttributePointer> attributePointers)
    : attribute_pointers(attributePointers), size(0) {
    for (auto& ap : attributePointers) {
      size += AttributeKindUtil::getSize(ap.kind);
    }
  }
};

}

#endif
