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

class Tracker {
 public:
  /**
   * @brief Construct a new Tracker object
   *
   */
  Tracker();

  /**
   * @brief Destroy the Tracker object
   *
   */
  ~Tracker();

  /**
   * @brief Draws bounding boxes around humans in a given frame
   *
   * @param input_image
   * @param centroids
   */
  void drawBoundingBoxes(cv::Mat input_image,
                         std::vector<std::vector<float>> centroids);

  /**
   * @brief Transforms the image coordinates to the Robot's Perspective
   *
   * @param centroids
   * @param world_coordinates
   * @return std::vector<std::vector<float>>
   */
  std::vector<std::vector<float>> getRobotPerspective(
  std::vector<std::vector<float>> centroids,
  std::vector<std::vector<float>> world_coordinates);

 private:
  std::vector<std::vector<float>> _intrinsic_params;
  std::vector<std::vector<float>> _extrinsic_params;
  std::vector<std::vector<float>> _robot_to_cam_transform;
  std::vector<std::vector<float>> _projection_matrix;
};

#endif  // INCLUDE_TRACK_HPP_
