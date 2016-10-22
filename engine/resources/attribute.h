#ifndef __BELLUM_ATTRIBUTE_H__
#define __BELLUM_ATTRIBUTE_H__

#include "../common.h"

namespace bellum {

struct Attribute {
  std::string name;
  uint32 location;
};

struct AttributeKind {
  uint8 id;
  uint32 size;
  std::string name;

  inline bool operator==(const AttributeKind& other) {
    return id == other.id;
  }

  inline bool operator!=(const AttributeKind& other) {
    return id != other.id;
  }

  static const AttributeKind kPosition;
  static const AttributeKind kColor;
  static const AttributeKind kNormal;
  static const AttributeKind kTextureCoordinate;

private:
  inline AttributeKind(uint8 id, uint32 size, const std::string& name)
    : id(id), size(size), name(name) {}
};

struct AttributePointer {
  AttributeKind kind;
  uint32 location;

  inline AttributePointer(AttributeKind kind, uint32 location)
    : kind(kind), location(location) {}
};

}

#endif
