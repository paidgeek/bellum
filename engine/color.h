#ifndef __BELLUM_COLOR_H__
#define __BELLUM_COLOR_H__

#include <ostream>
#include "common.h"
#include "math/math.h"
#include <cstdlib>

namespace bellum {

struct Vector4;

struct Color {
  float r;
  float g;
  float b;
  float a;

  inline Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
  inline Color(uint32 rgba);
  inline Color(uint8 r = 0, uint8 g = 0, uint8 b = 0, uint8 a = 255);
  inline Color(const float* data);

  inline Color(const Color& c);
  inline Color operator=(const Color& c);

  inline void set(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
  inline void set(uint32 rgba);
  inline void set(uint8 r = 0, uint8 g = 0, uint8 b = 0, uint8 a = 255);
  inline void set(const float* data);
  inline float& operator[](int32 i);

  inline float maxColorComponent() const;
  inline float minColorComponent() const;
  inline uint32 rgbaValue() const;
  inline uint32 rgbValue() const;
  inline Color& clamp();
  inline Color gamma(float value) const;

  inline static void makeHsv(float hue, float saturation, float value, Color& dst);
  static void getHsv(const Color& c, Vector4& dst);
  inline static void makeHex(const std::string& value, Color& dst);
  inline static void lerp(const Color& a, const Color& b, float t, Color& dst);

  inline static Color& clear();
  inline static Color& white();
  inline static Color& lightGray();
  inline static Color& gray();
  inline static Color& darkGray();
  inline static Color& black();
  inline static Color& red();
  inline static Color& pink();
  inline static Color& orange();
  inline static Color& yellow();
  inline static Color& green();
  inline static Color& magenta();
  inline static Color& cyan();
  inline static Color& blue();

  friend std::ostream& operator<<(std::ostream& os, const Color& color);
};

inline Color::Color(float r, float g, float b, float a)
  : r(r), g(g), b(b), a(a) {}

inline Color::Color(uint32 rgba)
  : Color(static_cast<uint8>(rgba & 0xFF),
          static_cast<uint8>((rgba >> 8) & 0xFF),
          static_cast<uint8>((rgba >> 16) & 0xFF),
          static_cast<uint8>((rgba >> 24) & 0xFF)) {}

inline Color::Color(uint8 r, uint8 g, uint8 b, uint8 a)
  : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

inline Color::Color(const Color& c)
  : r(c.r), g(c.g), b(c.b), a(c.a) {}

inline Color::Color(const float* data)
  : r(data[0]), g(data[1]), b(data[2]), a(data[3]) {}

inline Color Color::operator=(const Color& c) {
  r = c.r;
  g = c.g;
  b = c.b;
  a = c.a;
}

inline void Color::set(float r, float g, float b, float a) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

inline void Color::set(uint8 r, uint8 g, uint8 b, uint8 a) {
  this->r = r / 255.0f;
  this->g = g / 255.0f;
  this->b = b / 255.0f;
  this->a = a / 255.0f;
}

inline void Color::set(uint32 rgba) {
  set(
    static_cast<uint8>(rgba & 0xFF),
    static_cast<uint8>((rgba >> 8) & 0xFF),
    static_cast<uint8>((rgba >> 16) & 0xFF),
    static_cast<uint8>((rgba >> 24) & 0xFF)
  );
}

void Color::set(const float* data) {
  r = data[0];
  g = data[1];
  b = data[2];
  a = data[3];
}

float& Color::operator[](int32 i) {
  return *(&this->r + i);
}

float Color::maxColorComponent() const {
  return Math::max(r, Math::max(g, b));
}

float Color::minColorComponent() const {
  return Math::min(r, Math::min(g, b));
}

inline uint32 Color::rgbaValue() const {
  return 0xFF000000 |
         (static_cast<uint32>(r * 255.0f) << 16) |
         (static_cast<uint32>(g * 255.0f) << 8) |
         (static_cast<uint32>(b * 255.0f));
}

inline uint32 Color::rgbValue() const {
  return (static_cast<uint32>(r * 255.0f) << 16) |
         (static_cast<uint32>(g * 255.0f) << 8) |
         (static_cast<uint32>(b * 255.0f));
}

inline Color& Color::clamp() {
  set(
    Math::clamp(r, 0.0f, 1.0f),
    Math::clamp(g, 0.0f, 1.0f),
    Math::clamp(b, 0.0f, 1.0f),
    Math::clamp(a, 0.0f, 1.0f)
  );
  return *this;
}

inline Color Color::gamma(float value) const {
  float inv = 1.0f / value;
  return {
    Math::pow(r, inv),
    Math::pow(g, inv),
    Math::pow(b, inv),
    a
  };
}

inline void Color::makeHsv(float hue, float saturation, float value, Color& dst) {
  dst.set(value, value, value, 1.0f);

  if (saturation != 0.0f) {
    float max = value;
    float diff = value * saturation;
    float min = value - diff;
    float h = hue * 360.0f;

    if (h < 60f) {
      dst.set(max, h * diff / 60.0f + min, min);
    } else if (h < 120f) {
      dst.set(-(h - 120.0f) * diff / 60.0f + min, max, min);
    } else if (h < 180f) {
      dst.set(min, max, (h - 120.0f) * diff / 60.0f + min);
    } else if (h < 240f) {
      dst.set(min, -(h - 240.0f) * diff / 60.0f + min, max);
    } else if (h < 300f) {
      dst.set((h - 240.0f) * diff / 60.0f + min, min, max);
    } else if (h <= 360f) {
      dst.set(max, min, -(h - 360.0f) * diff / 60.0f + min);
    } else {
      dst.set(0.0f, 0.0f, 0.0f);
    }
  }

  dst.clamp();
}

inline void Color::makeHex(const std::string& value, Color& dst) {
  std::string hex = value[0] == '#' ? value.substr(1) : value;
  uint8 r = static_cast<uint8>(std::strtoul(value.substr(0, 2).c_str(), nullptr, 16));
  uint8 g = static_cast<uint8>(std::strtoul(value.substr(2, 4).c_str(), nullptr, 16));
  uint8 b = static_cast<uint8>(std::strtoul(value.substr(4, 6).c_str(), nullptr, 16));
  uint8 a = 255;
  if (hex.length() > 8) {
    a = static_cast<uint8>(std::strtoul(value.substr(6, 8).c_str(), nullptr, 16));
  }

  dst.set(r, g, b, a);
}

inline void Color::lerp(const Color& a, const Color& b, float t, Color& dst) {
  dst.set(
    a.r + (b.r - a.r) * t,
    a.g + (b.g - a.g) * t,
    a.b + (b.b - a.b) * t,
    a.a + (b.a - a.a) * t
  );
}

// Singletons
inline Color& Color::clear() {
  static Color value{0.0f, 0.0f, 0.0f, 0.0f};
  return value;
}

inline Color& Color::white() {
  static Color value{255, 255, 255};
  return value;
}

inline Color& Color::lightGray() {
  static Color value{192, 192, 192};
  return value;
}

inline Color& Color::gray() {
  static Color value{128, 128, 128};
  return value;
}

inline Color& Color::darkGray() {
  static Color value{64, 64, 64};
  return value;
}

inline Color& Color::black() {
  static Color value{0, 0, 0};
  return value;
}

inline Color& Color::red() {
  static Color value{255, 0, 0};
  return value;
}

inline Color& Color::pink() {
  static Color value{255, 175, 175};
  return value;
}

inline Color& Color::orange() {
  static Color value{255, 200, 0};
  return value;
}

inline Color& Color::yellow() {
  static Color value{255, 255, 0};
  return value;
}

inline Color& Color::green() {
  static Color value{0, 255, 0};
  return value;
}

inline Color& Color::magenta() {
  static Color value{255, 0, 255};
  return value;
}

inline Color& Color::cyan() {
  static Color value{0, 255, 255};
  return value;
}

inline Color& Color::blue() {
  static Color value{0, 0, 255};
  return value;
}

std::ostream& bellum::operator<<(std::ostream& os, const Color& c) {
  os << "Color(r: " << c.r << ", g: " << c.g << ", b: " << c.b << ", a: " << c.a << ")";
  return os;
}

}

#endif
