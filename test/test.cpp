/**
 * @file test.cpp
 * @author Aneesh Chodisetty (aneeshc@umd.edu)
 * @author Bhargav Kumar Soothram (bsoothra@umd.edu)
 * @author Joseph Pranadheer Reddy Katakam (jkatak@umd.edu)
 * @brief file to perform tests on the working pipeline
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

// Google test library for Unit Testing
#include <gtest/gtest.h>

// Test Candidates
#include "../include/model.hpp"
#include "../include/track.hpp"

TEST(complete_module_test, test_case_with_no_humans) {
    // setting up network
    Model model;
    model.setAllLabels("dependencies/coco.names");
    model.setNet("dependencies/yolov3.cfg", "dependencies/yolov3.weights");
    model.setConfidenceThresh(0.5);
    model.setNMSThreshold(0.4);

    // reading test image to detect humans
    cv::Mat frame(cv::imread("test_data/test_img_0.jpg"));

    // detect humans in the test image
    std::vector<cv::Mat> frame_outputs = model.predict(frame);

    model.postProcess(frame, frame_outputs);
    model.setNMSIndices();

    std::vector<cv::Rect> all_boxes = model.getBoxes();
    std::vector<int> nms_indices = model.getNMSIndices();

    // print detections
    std::cout << "/nNumber of Humans: " << static_cast<int>(nms_indices.size()) << std::endl;

    // checking to see if the number of detections are zero
    ASSERT_EQ(static_cast<int>(nms_indices.size()), 0);
}

TEST(complete_module_test, test_case_with_humans_in_clean_bg) {
    // setting up network
    Model model;
    model.setAllLabels("dependencies/coco.names");
    model.setNet("dependencies/yolov3.cfg", "dependencies/yolov3.weights");
    model.setConfidenceThresh(0.5);
    model.setNMSThreshold(0.4);

    // reading test image to detect humans
    cv::Mat frame(cv::imread("test_data/test_img_1.jpg"));

    // detect humans in the test image
    std::vector<cv::Mat> frame_outputs = model.predict(frame);

    model.postProcess(frame, frame_outputs);
    model.setNMSIndices();

    std::vector<cv::Rect> all_boxes = model.getBoxes();
    std::vector<int> nms_indices = model.getNMSIndices();

    // print detections
    std::cout << "/nNumber of Humans: " << static_cast<int>(nms_indices.size()) << std::endl;

    // checking to see if the number of detections are 4
    ASSERT_EQ(static_cast<int>(nms_indices.size()), 4);
}

TEST(complete_module_test, test_case_with_humans_in_noisy_bg) {
    // setting up network
    Model model;
    model.setAllLabels("dependencies/coco.names");
    model.setNet("dependencies/yolov3.cfg", "dependencies/yolov3.weights");
    model.setConfidenceThresh(0.5);
    model.setNMSThreshold(0.4);

    // reading test image to detect humans
    cv::Mat frame(cv::imread("test_data/test_img_2.jpg"));

    // detect humans in the test image
    std::vector<cv::Mat> frame_outputs = model.predict(frame);

    model.postProcess(frame, frame_outputs);
    model.setNMSIndices();

    std::vector<cv::Rect> all_boxes = model.getBoxes();
    std::vector<int> nms_indices = model.getNMSIndices();

    // print detections
    std::cout << "/nNumber of Humans: " << static_cast<int>(nms_indices.size()) << std::endl;

    // checking to see if the number of detections are not zero
    ASSERT_FALSE(nms_indices.empty());
}

TEST(Model_class_test, test_case_initializing_the_model) {
    // Network setup
    Model model;
    ASSERT_NO_THROW(model.setAllLabels("dependencies/coco.names"));
    ASSERT_NO_THROW(model.setNet("dependencies/yolov3.cfg", "dependencies/yolov3.weights"));
    ASSERT_NO_THROW(model.setConfidenceThresh(0.5));
    ASSERT_NO_THROW(model.setNMSThreshold(0.4));
}

TEST(HumanTracker_class_test, test_case_initializing_tracker_class) {
    // setting the initial parameters for the class
    HumanTracker humans;
    humans.setFocalLength(25);
    humans.setAvgHeight(170);
    ASSERT_EQ(humans.getFocalLength(), 25.00);
    ASSERT_EQ(humans.getAvgHeight(), 170.00);
}
