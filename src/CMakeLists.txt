
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_library(detect_and_track
            preprocess.cpp
            model.cpp
            detect.cpp
            ${CMAKE_SOURCE_DIR}/include/preprocess.hpp
            ${CMAKE_SOURCE_DIR}/include/model.hpp
            ${CMAKE_SOURCE_DIR}/include/detect.hpp
            )

target_include_directories(detect_and_track PUBLIC ../include)