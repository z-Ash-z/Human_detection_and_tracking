/**
 * Copyright (c) 2021 Aditi Ramadwar, Arunava Basu
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @file track.hpp
 * @author Aneesh Chodisetty (aneeshc@umd.edu)
 * @author Bhargav Kumar Soothram (bsoothra@umd.edu)
 * @author Joseph Pranadheer Reddy Katakam (jkatak@umd.edu)
 * @brief Header file for track.cpp
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
   * @brief Set the average height
   *
   * @param new_height
   */
  void setAvgHeight(double new_height);

  /**
   * @brief Get the average height
   *
   * @return double
   */
  const double getAvgHeight();

  /**
   * @brief Get the Robot Perspective
   *
   * @param boxes A vector of cv::Rect objects, containing all the bounding
   * boxes
   * @param indices NMS suppressed box indices
   * @return std::vector<cv::Point3d> The detected human coordinates with
   * respect to the robot's camera
   */
  const std::vector<cv::Point3d> getRobotPerspective(
      const std::vector<cv::Rect> &boxes, const std::vector<int> &indices);

 private:
  double _focal_length;    // The focal length of the camera (in mm)
  double _average_height;  // The average human height (in mm)
};

#endif  // INCLUDE_TRACK_HPP_
