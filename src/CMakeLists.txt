
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_library(human_detector_and_tracker_library
            model.cpp
            track.cpp
            ${CMAKE_SOURCE_DIR}/include/model.hpp
            ${CMAKE_SOURCE_DIR}/include/track.hpp
            )

target_include_directories(human_detector_and_tracker_library PUBLIC ../include)