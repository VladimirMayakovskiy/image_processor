#pragma once

#include "structures/pixel.h"
#include "structures/matrix.h"
using WORD = uint16_t;
using DWORD = uint32_t;
using LONG = int32_t;

namespace format_required {
const WORD BF_TYPE = static_cast<WORD>(0x4D42);
const WORD BI_BIT_COUNT = 24;
};  // namespace format_required

#pragma pack(push, 1)
struct BITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
};

struct BITMAPINFO {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
};
#pragma pack(pop)

class ImageHandler {
public:
    int Prepare(const std::string& filename);
    int CreateBmpFile(const std::string& filename);
    matrix<NormalizedPixel>& GetNormalizedMatrix();
    const matrix<NormalizedPixel>& GetNormalizedMatrix() const;

    const matrix<Pixel> GetPixelMatrix() const;
    matrix<Pixel>& GetPixelMatrix();

private:
    BITMAPFILEHEADER bmp_header_;
    BITMAPINFO bmp_info_;
    matrix<NormalizedPixel> normalized_matrix_;
    matrix<Pixel> matrix_;
};