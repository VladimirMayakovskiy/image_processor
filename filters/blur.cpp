#include "blur.h"
#include <valarray>

BlurFilter::BlurFilter(double sigma) : sigma_(sigma) {
    sigma_2_ = sigma_ * sigma_;
    coeff_ = 1.0 / pow(2 * M_PI * sigma_2_, 0.5);  // NOLINT
    radius_ = std::ceil(3 * sigma_);

    for (ssize_t r = -radius_; r <= radius_; ++r) {
        kernel_.push_back(coeff_ * exp(-static_cast<double>(r * r) / (2 * sigma_2_)));
    }
}
matrix<NormalizedPixel>& BlurFilter::Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) {
    ssize_t width = norm_px_arr.GetColsCnt();
    ssize_t height = norm_px_arr.GetRowsCnt();
    ssize_t k_rad_y = radius_;
    ssize_t k_rad_x = radius_;

    matrix<NormalizedPixel> arr(height, width);
    for (ssize_t y = 0; y < height; ++y) {
        for (ssize_t x = 0; x < width; ++x) {
            arr(y, x) = {0, 0, 0};
            for (ssize_t dx = -k_rad_x, i = 0; dx <= k_rad_x; ++dx, ++i) {
                arr(y, x).r += norm_px_arr.At(y, x + dx).r * kernel_[i];
                arr(y, x).g += norm_px_arr.At(y, x + dx).g * kernel_[i];
                arr(y, x).b += norm_px_arr.At(y, x + dx).b * kernel_[i];
            }

            arr(y, x).r = std::min(1., std::max(0., arr(y, x).r));
            arr(y, x).g = std::min(1., std::max(0., arr(y, x).g));
            arr(y, x).b = std::min(1., std::max(0., arr(y, x).b));
        }
    }

    for (ssize_t y = 1; y < height - 1; ++y) {
        for (ssize_t x = 1; x < width - 1; ++x) {
            norm_px_arr(y, x) = {0, 0, 0};
            for (ssize_t dy = -k_rad_y, i = 0; dy <= k_rad_y; ++dy, ++i) {
                norm_px_arr(y, x).r += arr.At(y + dy, x).r * kernel_[i];
                norm_px_arr(y, x).g += arr.At(y + dy, x).g * kernel_[i];
                norm_px_arr(y, x).b += arr.At(y + dy, x).b * kernel_[i];
            }
            norm_px_arr(y, x).r = std::min(1., std::max(0., norm_px_arr(y, x).r));
            norm_px_arr(y, x).g = std::min(1., std::max(0., norm_px_arr(y, x).g));
            norm_px_arr(y, x).b = std::min(1., std::max(0., norm_px_arr(y, x).b));

            px_arr(y, x) = {static_cast<uint8_t>(UINT8_MAX * norm_px_arr(y, x).b),
                            static_cast<uint8_t>(UINT8_MAX * norm_px_arr(y, x).g),
                            static_cast<uint8_t>(UINT8_MAX * norm_px_arr(y, x).r)};
        }
    }
    return norm_px_arr;
}