#include "attribute.h"

namespace bellum {

const AttributeKind AttributeKind::kPosition{0, 4, "POSITION"};
const AttributeKind AttributeKind::kColor{1, 4, "COLOR"};
const AttributeKind AttributeKind::kNormal{2, 3, "NORMAL"};
const AttributeKind AttributeKind::kTextureCoordinate{3, 2, "TEXTURE_COORDINATE"};

}
