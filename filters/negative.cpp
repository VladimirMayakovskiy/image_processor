
#include "negative.h"
matrix<NormalizedPixel>& NegativeFilter::Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) {
    ssize_t width = norm_px_arr.GetColsCnt();
    ssize_t height = norm_px_arr.GetRowsCnt();

    for (ssize_t y = 0; y < height; ++y) {
        for (ssize_t x = 0; x < width; ++x) {
            norm_px_arr(y, x) = {1 - norm_px_arr(y, x).r, 1 - norm_px_arr(y, x).g, 1 - norm_px_arr(y, x).b};
            px_arr(y, x) = {static_cast<uint8_t>(UINT8_MAX * norm_px_arr(y, x).b),
                            static_cast<uint8_t>(UINT8_MAX * norm_px_arr(y, x).g),
                            static_cast<uint8_t>(UINT8_MAX * norm_px_arr(y, x).r)};
        }
    }
    return norm_px_arr;
}