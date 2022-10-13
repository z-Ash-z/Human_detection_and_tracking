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

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>



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
   * @brief Returns model-predicted results given an input image
   *
   * @param input_image
   * @param centroids
   * @return double
   */
  double predict(cv::Mat input_image,
                 std::vector<std::vector<double>> centroids);

  /**
   * @brief Method to train the network, if need be
   *
   */
  void trainModel();

 private:
  double _pretrainedModel;
};

#endif  // INCLUDE_MODEL_HPP_
