#include <stdexcept>

#include "filter_creators.h"
#include "filters/grayscale.h"
#include "filters/crop.h"
#include "filters/sharp.h"
#include "filters/edge.h"
#include "filters/negative.h"
#include "filters/blur.h"
#include "filters/motion.h"
#include "filters/excessively.h"
Filter* CreateCropFilter(const FilterDescriptor& params) {
    if (params.params_cnt_ != 2) {
        throw std::invalid_argument(" Crop filter has 2 arguments: [-crop] [width, height].");
    }
    size_t width = 0;
    size_t height = 0;
    try {
        width = std::stoull(params.params_[0]);
        height = std::stoull(params.params_[1]);
        if (height == 0 || width == 0) {
            throw std::invalid_argument("");
        }
    } catch (...) {
        throw std::invalid_argument(" Crop arguments must be positive integer: [-crop] [width, height].");
    }
    return new CropFilter(width, height);
}
Filter* CreateGsFilter(const FilterDescriptor& params) {
    if (params.params_cnt_ != 0) {
        throw std::invalid_argument(" Grayscale filter has no arguments: [-gs].");
    }
    return new GsFilter();
}
Filter* CreateNegativeFilter(const FilterDescriptor& params) {
    if (params.params_cnt_ != 0) {
        throw std::invalid_argument(" Negative filter has no arguments: [-neg].");
    }
    return new NegativeFilter();
}
Filter* CreateSharpeningFilter(const FilterDescriptor& params) {
    if (params.params_cnt_ != 0) {
        throw std::invalid_argument(" Sharpening filter has no arguments: [-sharp].");
    }
    return new SharpeningFilter();
}
Filter* CreateEdgeFilter(const FilterDescriptor& params) {
    if (params.params_cnt_ != 1) {
        throw std::invalid_argument(" Edge filter has 1 argument: [-edge] [threshold].");
    }
    double threshold = 0;
    try {
        threshold = std::stod(params.params_[0]);
    } catch (...) {
        throw std::invalid_argument(": Edge argument must be a real number: [-edge] [threshold].");
    }
    return new EdgeFilter(threshold);
}
Filter* CreateBlurFilter(const FilterDescriptor& params) {
    if (params.params_cnt_ != 1) {
        throw std::invalid_argument(" Blur filter has 1 argument: [-blur] [sigma].");
    }
    double sigma = 0;
    try {
        sigma = std::stod(params.params_[0]);
    } catch (...) {
        throw std::invalid_argument(" Blur argument must be a real number: [-blur] [sigma].");
    }
    return new BlurFilter(sigma);
}
Filter* CreateMotionFilter(const FilterDescriptor& params) {
    if (params.params_cnt_ != 0) {
        throw std::invalid_argument(" Motion filter has no arguments: [-motion].");
    }
    return new MotionFilter();
}
Filter* CreateExcessFilter(const FilterDescriptor& params) {
    if (params.params_cnt_!=0){
        throw std::invalid_argument(" Excess filter has no arguments: [-ex].");
    }
    return new ExcessivelyFilter();
}
