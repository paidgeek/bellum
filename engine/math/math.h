#ifndef BELLUM_MATH_H
#define BELLUM_MATH_H

#include "../common.h"
#include <cmath>

namespace bellum {

class Math {
public:
  static constexpr float kE = 2.7182818284590452354f;
  static constexpr float kPi = 3.14159265358979323846f;
  static constexpr float kSqrt2 = 1.41421356237309504880f;
  static constexpr float kPi2 = kPi * 2.0f;
  static constexpr float kRadToDeg = 180.0f / kPi;
  static constexpr float kDegToRad = kPi / 180.0f;

  static inline float sqrt(float x) {
    return std::sqrt(x);
  }

  static inline float pow(float x, float y) {
    return std::pow(x, y);
  }

  static inline float sin(float x) {
    return std::sin(x);
  }

  static inline float asin(float x) {
    return std::asin(x);
  }

  static inline float cos(float x) {
    return std::cos(x);
  }

  static inline float acos(float x) {
    return std::acos(x);
  }

  static inline float tan(float x) {
    return std::tan(x);
  }

  static inline float atan(float x) {
    return std::atan(x);
  }

  static inline float atan2(float y, float x) {
    return std::atan2(y, x);
  }

  static inline float abs(float x) {
    return x < 0.0f ? -x : x;
  }

  static inline float max(float a, float b) {
    return a < b ? b : a;
  }

  static inline float min(float a, float b) {
    return a < b ? a : b;
  }

  static inline float clamp(float x, float min, float max) {
    return x < min ? min : x > max ? max : x;
  }

  static inline float floor(float x) {
    return std::floor(x);
  }

  static inline int32 floorToInt(float x) {
    return static_cast<int32>(std::floor(x));
  }

  static inline int32 roundToInt(float x) {
    return static_cast<int32>(std::round(x));
  }

  static inline float sign(float x) {
    return x < 0.0f ? -1.0f : x > 0.0f ? 1.0f : 0.0f;
  }

  static inline float lerp(float a, float b, float t) {
    return a + (b - a) * t;
  }
};

}

#endif
