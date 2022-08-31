#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdint>
#include <vector>
#include <iosfwd>

#include "CommonDefines.h"

struct PackedImage {
  explicit PackedImage(const Resolution& res);

  bool operator==(const PackedImage& other) const;
  friend std::istream& operator>>(std::istream& istream, PackedImage& img);

  Resolution resolution;
  std::vector<Pixel> pixels;
};

struct StrideImage {
  explicit StrideImage(const Resolution& res);

  bool operator==(const StrideImage& other) const;
  friend std::istream& operator>>(std::istream& istream, StrideImage& img);

  Resolution resolution;
  std::vector<uint8_t> redPixels;
  std::vector<uint8_t> greenPixels;
  std::vector<uint8_t> bluePixels;
  std::vector<uint8_t> alphaPixels;

  [[nodiscard]] Pixel getPixelAt(size_t index) const
  {
      return Pixel {
          .red = redPixels[index],
          .green = greenPixels[index],
          .blue = bluePixels[index],
          .alpha = alphaPixels[index],
      };
  }

  [[nodiscard]] Pixel getPixelAt(uint32_t x, uint32_t y) const
  {
      const uint32_t index = y * resolution.height + x;
      return Pixel {
          .red = redPixels[index],
          .green = greenPixels[index],
          .blue = bluePixels[index],
          .alpha = alphaPixels[index]};
  }
};

#endif /* IMAGE_H_ */
