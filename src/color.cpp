#include "color.h"

bool operator==(const Color& lhs, const Color& rhs) {
  return lhs.mRed == rhs.mRed
         && lhs.mGreen == rhs.mGreen
         && lhs.mBlue == rhs.mBlue
         && lhs.mAlpha == rhs.mAlpha;
}

bool operator!=(const Color& lhs, const Color& rhs) { return !(lhs == rhs); }

std::ostream& operator<<(std::ostream& os, const Color& color) {
  os << "Red " << static_cast<int>(color.mRed) 
     << " Blue " << static_cast<int>(color.mBlue) 
     << " Green " << static_cast<int>(color.mGreen)
     << " Alpha " << static_cast<int>(color.mAlpha);
  return os;
}