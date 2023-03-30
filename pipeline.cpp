
#include "pipeline.h"

const std::map<std::string, Pipeline::FilterCreatorPtr> Pipeline::make_filters({
    {"crop", [](const FilterDescriptor& filter) { return CreateCropFilter(filter); }},
    {"gs", [](const FilterDescriptor& filter) { return CreateGsFilter(filter); }},
    {"neg", [](const FilterDescriptor& filter) { return CreateNegativeFilter(filter); }},
    {"sharp", [](const FilterDescriptor& filter) { return CreateSharpeningFilter(filter); }},
    {"edge", [](const FilterDescriptor& filter) { return CreateEdgeFilter(filter); }},
    {"blur", [](const FilterDescriptor& filter) { return CreateBlurFilter(filter); }},
    {"motion", [](const FilterDescriptor& filter) { return CreateMotionFilter(filter); }},
    {"ex", [](const FilterDescriptor& filter) { return CreateExcessFilter(filter); }},
});

Pipeline::Pipeline(const std::vector<FilterDescriptor>& params) {
    LoadFilters(params);
}
int Pipeline::LoadFilters(const std::vector<FilterDescriptor>& params) {
    for (const FilterDescriptor& filter : params) {
        std::map<std::string, Pipeline::FilterCreatorPtr>::const_iterator it = make_filters.find(filter.name_);
        if (it == make_filters.end()) {
            throw std::logic_error("[ -" + filter.name_ + " ]" + ": no such filter found.");
        }
        filters_.push_back(it->second(filter));
    }
    return 0;
}

int Pipeline::ApplyAll(matrix<NormalizedPixel>& norm_img, matrix<Pixel>& img) const {
    for (Filter* filter : filters_) {
        filter->Apply(norm_img, img);
    }
    return 0;
}

Pipeline::~Pipeline() {
    for (Filter* filter : filters_) {
        delete filter;
    }
}