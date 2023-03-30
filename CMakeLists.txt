cmake_minimum_required(VERSION 3.24)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(image_processor main.cpp pipeline.h pipeline.cpp
        filter_creators.h filter_creators.cpp
        controller.h controller.cpp
        bmp_handler.h bmp_handler.cpp
        structures/filter_descriptor.h structures/matrix.h structures/pixel.h
        filters/base.cpp filters/base.h cmd_handler.cpp cmd_handler.h filters/blur.cpp filters/blur.h filters/crop.cpp filters/crop.h filters/edge.cpp filters/edge.h filters/grayscale.cpp filters/grayscale.h filters/motion.cpp filters/motion.h filters/negative.cpp filters/negative.h filters/sharp.cpp filters/sharp.h filters/excessively.cpp filters/excessively.h)
