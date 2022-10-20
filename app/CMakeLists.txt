add_executable(human_detect_and_track_app main.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(human_detect_and_track_app PUBLIC human_detector_and_tracker_library ${OpenCV_LIBS})
