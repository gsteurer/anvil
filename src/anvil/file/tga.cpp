#include "anvil/file/tga.h"

#include <fstream>
#include <iostream>

namespace anvil {
namespace file {
namespace tga {

Color::Color(float r, float g, float b, float a) : b(b * 255), g(g * 255), r(r * 255), a(a * 255) {}
Color::Color() {}
Color::~Color() {}

Image::Image(isize_t width, isize_t height, isize_t bytesPerPixel) {
    this->bytesPerPixel = bytesPerPixel;
    this->width = width;
    this->height = height;
    isize_t numBytes = width * height * bytesPerPixel;
    data = new u8_t[numBytes];
    memset(data, 0, numBytes);
}

Image::~Image() {
    delete[] data;
}

bool Image::WriteTGA(std::string filename) {
    std::ofstream out;
    out.open(filename, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "can't open file " << filename << "\n";
        out.close();
        return false;
    }

    TGAHeader header;
    memset((void *)&header, 0, sizeof(header));
    header.pixelDepth = bytesPerPixel << 3;
    header.imageWidth = width;
    header.imageHeight = height;
    header.imageType = 2;
    header.imageDescriptor = 0x20;  // top left; bits 3-0 are alpha channel depth, bits 5&4 are direction

    out.write((char *)&header, sizeof(header));
    if (!out.good()) {
        out.close();
        std::cerr << "unable to write header\n";
        return false;
    }
    out.write((char *)data, width * height * bytesPerPixel);
    if (!out.good()) {
        std::cerr << "unable to write image data\n";
        out.close();
        return false;
    }

    unsigned char developer_area_ref[4] = {0, 0, 0, 0};
    out.write((char *)developer_area_ref, sizeof(developer_area_ref));
    if (!out.good()) {
        std::cerr << "unable to write developer area ref\n";
        out.close();
        return false;
    }

    unsigned char extension_area_ref[4] = {0, 0, 0, 0};
    out.write((char *)extension_area_ref, sizeof(extension_area_ref));
    if (!out.good()) {
        std::cerr << "unable to write extension area ref\n";
        out.close();
        return false;
    }

    unsigned char footer[18] = {'T', 'R', 'U', 'E', 'V', 'I', 'S', 'I', 'O', 'N', '-', 'X', 'F', 'I', 'L', 'E', '.', '\0'};
    out.write((char *)footer, sizeof(footer));
    if (!out.good()) {
        std::cerr << "unable to write tga footer\n";
        out.close();
        return false;
    }
    out.close();
    return true;
}

bool Image::Set(isize_t x, isize_t y, Color c) {
    if (data == nullptr || x < 0 || y < 0 || x >= width || y >= height)
        return false;
    memcpy(data + (x + y * width) * bytesPerPixel, c.raw, bytesPerPixel);
    return true;
}

Color Image::Get(isize_t x, isize_t y) const {
    if (data == nullptr || x < 0 || y < 0 || x >= width || y >= height)
        return Color(0, 0, 0, 0);

    uint8_t *idx = data + (x + y * width) * bytesPerPixel;
    return Color(*idx, *(idx + 1), *(idx + 2), *(idx + 3));
}

void Image::Clear(Color c) {
    for (isize_t idx = 0; idx < width; idx++)
        for (isize_t jdx = 0; jdx < height; jdx++)
            Set(idx, jdx, c);
}

isize_t Image::Width() const {
    return width;
}
isize_t Image::Height() const {
    return height;
}

}  // namespace tga
}  // namespace file
}  // namespace anvil