#pragma once

#include <iostream>

struct Color {
  uint8_t mRed;
  uint8_t mGreen;
  uint8_t mBlue;
  uint8_t mAlpha;

  Color(): mRed(0), mGreen(0), mBlue(0), mAlpha(255) {}
  Color(uint8_t r, uint8_t g, uint8_t b): mRed(r), mGreen(g), mBlue(b), mAlpha(255) {}
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a): mRed(r), mGreen(g), mBlue(b), mAlpha(a) {}
};

bool operator==(const Color& lhs, const Color& rhs);

bool operator!=(const Color& lhs, const Color& rhs);

std::ostream& operator<<(std::ostream& os, const Color& pixel);