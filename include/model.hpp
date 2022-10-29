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

#include <string>
#include <vector>
#include <fstream>
#include <opencv2/dnn.hpp>
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
  std::vector<cv::Mat> predict(cv::Mat input_image);

  /**
   * @brief Get the output names of the object
   *
   * @return std::vector<std::string>
   */
  std::vector<std::string> getOutputsNames();

  /**
   * @brief Set up the network
   *
   * @param configuration
   * @param model
   */
  void setNet(std::string configuration, std::string model);

  /**
   * @brief Set the confidence threshold
   *
   * @param conf_thresh
   */
  void setConfidenceThresh(double conf_thresh);

  /**
   * @brief Set the threshold for non-maximal suppression
   *
   * @param nms_thresh
   */
  void setNMSThreshold(double nms_thresh);

  /**
   * @brief Identifies humans in a frame based on a confidence score
   *
   * @param frame
   * @param dnn_outs
   */
  void postProcess(const cv::Mat &frame, const std::vector<cv::Mat> &dnn_outs);

  /**
   * @brief Get all the bounding boxes
   *
   * @return std::vector<cv::Rect>
   */
  std::vector<cv::Rect> getBoxes();

  /**
   * @brief Identify and set all non-maximally suppressed indices to get
   *        the boxes, confidence scores and class IDs associated to those
   * indices
   */
  void setNMSIndices();

  /**
   * @brief Returns a vector containing all the non-maximal-suppressed indices
   *
   * @return std::vector<int>
   */
  std::vector<int> getNMSIndices();

  /**
   * @brief Draws the best bounding box around an identified human
   *
   * @param frame
   * @return cv::Mat
   */
  cv::Mat drawBoxes(cv::Mat *frame);

 private:
  std::vector<std::string> _all_labels;
  cv::dnn::Net _net;
  double _min_confidence_score;
  double _nms_threshold;
  std::vector<int> _classIds;
  std::vector<float> _confidences;
  std::vector<cv::Rect> _boxes;
  std::vector<int> _nms_indices;
};

#endif  // INCLUDE_MODEL_HPP_
