
#include <fstream>
#include <iostream>
#include "bmp_handler.h"

int ImageHandler::Prepare(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        throw std::runtime_error(filename + ": no such file or directory.");
    }

    file.read(reinterpret_cast<char *>(&bmp_header_), sizeof(bmp_header_));
    file.read(reinterpret_cast<char *>(&bmp_info_), sizeof(bmp_info_));

    if (bmp_header_.bfType != format_required::BF_TYPE) {
        throw std::runtime_error(filename + ": not a BMP file.");
    }

    if (bmp_info_.biBitCount != format_required::BI_BIT_COUNT) {
        throw std::runtime_error(filename + ": only 24-bit BMPs are supported.");
    }

    if (bmp_info_.biCompression != 0) {
        throw std::runtime_error(filename + ": compression is not supported.");
    }

    if (bmp_info_.biClrUsed != 0 || bmp_info_.biClrImportant != 0) {
        throw std::runtime_error(filename + ": color table is not supported.");
    }

    ssize_t width = bmp_info_.biWidth;
    ssize_t height = bmp_info_.biHeight;

    file.seekg(bmp_header_.bfOffBits);

    normalized_matrix_.Resize(height, width);
    matrix_.Resize(height, width);

    size_t padding = (4 - (width * sizeof(Pixel)) % 4) % 4;

    if (height < 0) {
        for (ssize_t y = 0; y < height; ++y) {
            for (ssize_t x = 0; x < width; ++x) {
                Pixel px;
                file.read(reinterpret_cast<char *>(&px), sizeof(px));
                normalized_matrix_(y, x) = {px.r * 1.0 / UINT8_MAX, px.g * 1.0 / UINT8_MAX, px.b * 1.0 / UINT8_MAX};
                matrix_(y, x) = px;
            }
            uint8_t plug = 0;
            for (size_t i = 0; i < padding && y > 0; ++i) {
                file.read(reinterpret_cast<char *>(&plug), sizeof(plug));
            }
        }
    } else if (height > 0) {
        for (ssize_t y = height - 1; y >= 0; --y) {
            for (ssize_t x = 0; x < width; ++x) {
                Pixel px;
                file.read(reinterpret_cast<char *>(&px), sizeof(px));
                normalized_matrix_(y, x) = {px.r * 1.0 / UINT8_MAX, px.g * 1.0 / UINT8_MAX, px.b * 1.0 / UINT8_MAX};
                matrix_(y, x) = px;
            }
            uint8_t plug = 0;
            for (size_t i = 0; i < padding && y > 0; ++i) {
                file.read(reinterpret_cast<char *>(&plug), sizeof(plug));
            }
        }
    } else {
        file.close();
        throw std::runtime_error(filename + ": read failure.");
    }

    file.close();
    return 0;
}
int ImageHandler::CreateBmpFile(const std::string &filename) {
    std::ofstream file(filename, std::ios::binary | std::ios::out);

    if (!file.is_open()) {
        throw std::runtime_error(filename + ": no such file or directory");
    }

    bmp_info_.biWidth = static_cast<LONG>(normalized_matrix_.GetColsCnt());
    bmp_info_.biHeight = static_cast<LONG>(normalized_matrix_.GetRowsCnt());
    ssize_t width = bmp_info_.biWidth;
    ssize_t height = bmp_info_.biHeight;

    size_t padding = (4 - (width * sizeof(Pixel)) % 4) % 4;
    bmp_header_.bfSize = (padding + bmp_info_.biWidth) * bmp_info_.biHeight * sizeof(Pixel) + sizeof(BITMAPFILEHEADER) +
                         sizeof(BITMAPINFO);

    file.write(reinterpret_cast<const char *>(&bmp_header_), sizeof(bmp_header_));
    file.write(reinterpret_cast<const char *>(&bmp_info_), sizeof(bmp_info_));

    if (height < 0) {
        for (ssize_t y = 0; y < height; ++y) {
            for (ssize_t x = 0; x < width; ++x) {
                file.write(reinterpret_cast<const char *>(&matrix_(y, x)), sizeof(Pixel));
            }
            uint8_t plug = 0;
            for (size_t i = 0; i < padding; ++i) {
                file.write(reinterpret_cast<char *>(&plug), sizeof(plug));
            }
        }
    } else if (height > 0) {
        for (ssize_t y = height - 1; y >= 0; --y) {
            for (ssize_t x = 0; x < width; ++x) {
                file.write(reinterpret_cast<const char *>(&matrix_(y, x)), sizeof(Pixel));
            }
            uint8_t plug = 0;
            for (size_t i = 0; i < padding; ++i) {
                file.write(reinterpret_cast<char *>(&plug), sizeof(plug));
            }
        }
    }
    file.close();
    return 0;
}

matrix<NormalizedPixel> &ImageHandler::GetNormalizedMatrix() {
    return normalized_matrix_;
}

const matrix<NormalizedPixel> &ImageHandler::GetNormalizedMatrix() const {
    return normalized_matrix_;
}

matrix<Pixel> &ImageHandler::GetPixelMatrix() {
    return matrix_;
}

const matrix<Pixel> ImageHandler::GetPixelMatrix() const {
    return matrix_;
}
