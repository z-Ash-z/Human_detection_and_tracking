set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    test.cpp
    ../src/model.cpp
    ../src/track.cpp
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include
                                           ../vendor/googletest/googlemock/include)
target_link_libraries(cpp-test PUBLIC human_detector_and_tracker_library gtest ${OpenCV_LIBS})