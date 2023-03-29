#pragma once
#include "base.h"
class CropFilter : public Filter {
public:
    CropFilter(size_t width, size_t height);
    matrix<NormalizedPixel>& Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) override;

private:
    size_t width_;
    size_t height_;
};
