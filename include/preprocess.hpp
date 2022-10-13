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

#ifndef INCLUDE_PREPROCESS_HPP_
#define INCLUDE_PREPROCESS_HPP_

#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>

class Preprocess {
 public:
  /**
   * @brief Constructor for a preprocess object
   *
   */
  Preprocess();

  /**
   * @brief Destructor for a preprocess object
   *
   */
  ~Preprocess();

  /**
   * @brief Function to resize/rescale the inputs as desired
   *
   * @param input_image
   * @param flags
   */
  void preprocess(cv::Mat input_image, std::string flags);
};

#endif  // INCLUDE_PREPROCESS_HPP_
