/**
 * @file preprocess.hpp
 * @author Aneesh Chodisetty (aneeshc@umd.edu)
 * @author Bhargav Kumar Soothram (bsoothra@umd.edu)
 * @author Joseph Pranadheer Reddy Katakam (jkatak@umd.edu)
 * @brief Header file for model.cpp
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef INCLUDE_MODEL_HPP_
#define INCLUDE_MODEL_HPP_

#include <fstream>
#include <string>
#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>
#include <opencv2/opencv.hpp>


class Model {
 public:
  /**
   * @brief Construct a new Model object
   *
   */
  Model();

  /**
   * @brief Destroy the Model object
   *
   */
  ~Model();

  /**
   * @brief Set all the labels
   *
   * @param file_path
   */
  void setAllLabels(std::string file_path);

  /**
   * @brief Returns model-predicted results given an input image
   *
   * @param input_image
   * @return cv::Mat
   */
  cv::Mat predict(cv::Mat input_image);

  void setNet(std::string configuration, std::string model);

  std::vector<std::string> all_labels;

 private:
  cv::dnn::Net net;
};

#endif  // INCLUDE_MODEL_HPP_
