cmake_minimum_required(VERSION 3.18)
project(cpp)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(.)
include_directories(utils)

add_executable(eye_filter
        main.cpp
        utils/CommonDefines.h
        utils/EyePatterns.h
        utils/FileParser.h
        utils/FunctionTracer.h
        utils/Image.cpp
        utils/Image.h
        utils/SolutionEvaluator.h
        Solution.h
        Solution.cpp)
