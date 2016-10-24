#ifndef __BELLUM_RANDOM_H__
#define __BELLUM_RANDOM_H__

#include "common.h"
#include "color.h"

namespace bellum {

class Random {
public:
  static float value() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }

  static Color color() {
    return {value(), value(), value(), 1.0f};
  }

private:
  Random(){};
};

}

#endif
