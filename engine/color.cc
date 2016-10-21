#include "color.h"
#include "math/vector4.h"

namespace bellum {

void Color::getHsv(const Color& c, Vector4& dst) {
  dst.set(0.0f, 0.0f, 0.0f, c.a);

  float r = c.r;
  float g = c.g;
  float b = c.b;
  float max = c.maxColorComponent();

  if (max <= 0.0f) {
    return;
  }

  float min = c.minColorComponent();
  float diff = max - min;

  if (max > min) {
    if (g == max) {
      dst.x = (b - r) / diff * 60.0f + 120.0f;
    } else if (b == max) {
      dst.x = (r - g) / diff * 60.0f + 240.0f;
    } else if (b > g) {
      dst.x = (g - b) / diff * 60.0f + 360.0f;
    } else {
      dst.x = (g - b) / diff * 60.0f;
    }

    if (dst.x < 0.0f) {
      dst.x += 360.0f;
    }
  } else {
    dst.x = 0.0f;
  }

  dst.x *= 1.0f / 360.0f;
  dst.y = diff / max;
  dst.z = max;
}

}
