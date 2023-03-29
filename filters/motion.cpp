#include "motion.h"

const std::vector<double> MotionFilter::KERNEL({0.2, 0, 0, 0, 0, 0,   0.2, 0, 0, 0, 0, 0,  0.2,
                                                0,   0, 0, 0, 0, 0.2, 0,   0, 0, 0, 0, 0.2});

matrix<NormalizedPixel>& MotionFilter::Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) {
    ssize_t width = px_arr.GetColsCnt();
    ssize_t height = px_arr.GetRowsCnt();
    ssize_t k_rad_y = 2;
    ssize_t k_rad_x = 2;

    matrix<NormalizedPixel> arr(height, width);
    for (ssize_t y = 0; y < height; ++y) {
        for (ssize_t x = 0; x < width; ++x) {
            arr(y, x) = {0, 0, 0};
            for (ssize_t dy = -k_rad_y, i = 0; dy <= k_rad_y; ++dy) {
                for (ssize_t dx = -k_rad_x; dx <= k_rad_x; ++dx, ++i) {
                    arr(y, x).r += norm_px_arr.At(y + dy, x + dx).r * KERNEL[i];
                    arr(y, x).g += norm_px_arr.At(y + dy, x + dx).g * KERNEL[i];
                    arr(y, x).b += norm_px_arr.At(y + dy, x + dx).b * KERNEL[i];
                }
            }
            arr(y, x).r = std::min(1., std::max(0., arr(y, x).r));
            arr(y, x).g = std::min(1., std::max(0., arr(y, x).g));
            arr(y, x).b = std::min(1., std::max(0., arr(y, x).b));
            px_arr(y, x) = {static_cast<uint8_t>(arr(y, x).b * UINT8_MAX),
                            static_cast<uint8_t>(arr(y, x).g * UINT8_MAX),
                            static_cast<uint8_t>(arr(y, x).r * UINT8_MAX)};
        }
    }
    norm_px_arr = arr;
    return norm_px_arr;
}