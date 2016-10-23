#ifndef __BELLUM_ATTRIBUTE_H__
#define __BELLUM_ATTRIBUTE_H__

#include "../common.h"

namespace bellum {

struct Attribute {
  std::string name;
  uint32 location;
};

enum class AttributeKind {
  POSITION,
  COLOR,
  NORMAL,
  TEXTURE_COORDINATE
};

namespace AttributeKindUtil {

static uint32 getSize(AttributeKind kind) {
  switch (kind) {
    case AttributeKind::POSITION:
      return 3;
    case AttributeKind::COLOR:
      return 4;
    case AttributeKind::NORMAL:
      return 3;
    case AttributeKind::TEXTURE_COORDINATE:
      return 2;
  }
  return 0;
}

static const char* getName(AttributeKind kind) {
  switch (kind) {
    case AttributeKind::POSITION:
      return "POSITION";
    case AttributeKind::COLOR:
      return "COLOR";
    case AttributeKind::NORMAL:
      return "NORMAL";
    case AttributeKind::TEXTURE_COORDINATE:
      return "UV";
  }
  return nullptr;
}

}

struct AttributePointer {
  AttributeKind kind;
  uint32 location;

  inline AttributePointer(AttributeKind kind, uint32 location)
    : kind(kind), location(location) {}
};

}

#endif
