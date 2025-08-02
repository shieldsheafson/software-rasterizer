#pragma once

#include "color.h"

#include <cstring>

class RenderTarget {
  private:
    int mWidth;
    int mHeight;
    void* mPixels;
    int mPitch;
  public:
    RenderTarget(int width, int height)
      : mWidth(width), mHeight(height) {}

    int GetWidth() const { return mWidth; }
    int GetHeight() const { return mHeight; }

    void SetPixels(void* pixels) { mPixels = pixels; }
    void SetPitch(int pitch) { mPitch = pitch; }
    void SetPixel(unsigned int x, unsigned int y, Color color) {
      uint8_t* pixel = (uint8_t*) mPixels + y * mPitch + x * 4;
      pixel[0] = color.mAlpha; 
      pixel[1] = color.mGreen;
      pixel[2] = color.mBlue;
      pixel[3] = color.mRed;
    }

    void Clear() {
      memset(mPixels, 0, mHeight * mPitch);
    }
};