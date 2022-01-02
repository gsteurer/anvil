#pragma once

#include <stddef.h>  // size_t
#include <stdint.h>  // intn_t
#include <string.h>  // memset

#include <string>

namespace anvil {
namespace file {
namespace tga {

// CREDIT: https://github.com/ssloy/tinyrenderer/blob/909fe20934ba5334144d2c748805690a1fa4c89f/tgaimage.cpp

#pragma pack(push, 1)
// https://en.wikipedia.org/wiki/Truevision_TGA#Header
struct TGAHeader {
    int8_t idLength;      // length of image id field; contains any metadata i.e serial number or date and type
    int8_t colorMapType;  // whether a color map is included; 0 not present, 1 present, 2-127 truevision, 128-255 dev use
    int8_t imageType;     // compression and color type;
    // color map specification
    int16_t colorMapFirstEntryIndex;
    int16_t colorMapLength;
    int8_t colorMapEntrySize;
    // image specification
    int16_t xOrigin;
    int16_t yOrigin;
    int16_t imageWidth;
    int16_t imageHeight;
    int8_t pixelDepth;  // bits per pixel
    int8_t imageDescriptor;
};
#pragma pack(pop)

class Color {
   public:
    Color(float r, float g, float b, float a);
    union {
        struct {
            uint8_t b, g, r, a;
        };
        uint8_t raw[4];
        uint32_t val;
    };
    ~Color();

   private:
    Color();
};

class Image {
   public:
    Image(size_t width, size_t height, size_t bytesPerPixel);
    ~Image();
    bool WriteTGA(std::string filename);
    bool Set(size_t x, size_t y, Color c);
    Color Get(size_t x, size_t y);
    void Clear(Color c);

   private:
    size_t width;
    size_t height;
    size_t bytesPerPixel;
    uint8_t *data;
    Image();
};

}  // namespace tga
}  // namespace file
}  // namespace anvil