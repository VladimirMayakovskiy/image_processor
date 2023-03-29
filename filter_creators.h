#pragma once

#include "structures/filter_descriptor.h"
#include "filters/base.h"
Filter* CreateCropFilter(const FilterDescriptor& params);
Filter* CreateGsFilter(const FilterDescriptor& params);
Filter* CreateNegativeFilter(const FilterDescriptor& params);
Filter* CreateSharpeningFilter(const FilterDescriptor& params);
Filter* CreateEdgeFilter(const FilterDescriptor& params);
Filter* CreateBlurFilter(const FilterDescriptor& params);
Filter* CreateMotionFilter(const FilterDescriptor& params);
