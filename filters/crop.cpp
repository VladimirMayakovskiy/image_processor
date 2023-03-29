
#include "crop.h"
CropFilter::CropFilter(size_t width, size_t height) : width_(width), height_(height) {
}
matrix<NormalizedPixel>& CropFilter::Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) {
    width_ = std::min<size_t>(width_, px_arr.GetColsCnt());
    height_ = std::min<size_t>(height_, px_arr.GetRowsCnt());
    norm_px_arr.Resize(height_, width_);
    px_arr.Resize(height_, width_);
    return norm_px_arr;
}