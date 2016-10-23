#ifndef __BELLUM_VECTOR2_H__
#define __BELLUM_VECTOR2_H__

#include "../common.h"

namespace bellum {

struct Vector2 {
  float x;
  float y;

  inline Vector2(float x = 0.0f, float y = 0.0f);
};

Vector2::Vector2(float x, float y)
  : x(x), y(y) {}

}

#endif
