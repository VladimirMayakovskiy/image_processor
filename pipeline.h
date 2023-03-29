#pragma once

#include "filters/base.h"
#include "structures/filter_descriptor.h"
#include "structures/matrix.h"
#include "structures/pixel.h"
#include "filter_creators.h"
#include <map>
#include <functional>
class Pipeline {
private:
    std::vector<Filter*> filters_;

    using FilterCreatorPtr = std::function<Filter*(const FilterDescriptor&)>;

    static const std::map<std::string, FilterCreatorPtr> make_filters;

public:
    explicit Pipeline(const std::vector<FilterDescriptor>& params);
    int LoadFilters(const std::vector<FilterDescriptor>& params);
    int ApplyAll(matrix<NormalizedPixel>& norm_img, matrix<Pixel>& img) const;
    ~Pipeline();
};
