/**
 * @file preprocess.hpp
 * @author Aneesh Chodisetty (aneeshc@umd.edu)
 * @author Bhargav Kumar Soothram (bsoothra@umd.edu)
 * @author Joseph Pranadheer Reddy Katakam (jkatak@umd.edu)
 * @brief Header file for preprocess.cpp
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef INCLUDE_TRACK_HPP_
#define INCLUDE_TRACK_HPP_

#include <vector>
#include <opencv2/core/types.hpp>

class HumanTracker {
 public:
  /**
   * @brief Construct a new Human Tracker object
   *
   */
  HumanTracker();

  /**
   * @brief Destroy the Human Tracker object
   *
   */
  ~HumanTracker();

  /**
   * @brief Set the Focal Length of the camera
   * 
   * @param new_f 
   */
  void setFocalLength(double new_f);

  /**
   * @brief Get the Focal Length of the camera
   * 
   * @return const double 
   */
  const double getFocalLength();

  /**
   * @brief Get the Robot Perspective
   * 
   * @param boxes A vector of cv::Rect objects, containing all the bounding boxes.
   * @param indices NMS suppressed box indices.
   * @return std::vector<cv::Point3d> The detected human coordinates with respect to the robot's camera.
   */
  const std::vector<cv::Point3d> getRobotPerspective(std::vector<cv::Rect> &boxes, std::vector<int> &indices);

 private:
  double _focal_length;     // The focal length of the camera (in mm)
  double _average_height;   // The average human height (in mm)
};

#endif  // INCLUDE_TRACK_HPP_
