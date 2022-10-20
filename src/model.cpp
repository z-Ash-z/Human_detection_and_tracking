/**
 * @file preprocess.hpp
 * @author Aneesh Chodisetty (aneeshc@umd.edu)
 * @author Bhargav Kumar Soothram (bsoothra@umd.edu)
 * @author Joseph Pranadheer Reddy Katakam (jkatak@umd.edu)
 * @brief Draws inferences for the data given
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <model.hpp>


Model::Model() {}

Model::~Model() {}

void Model::setAllLabels(std::string file_path) {
  std::ifstream input_stream(file_path.c_str());
  std::string line;
  while (getline(input_stream, line)) {
    std::cout << line << std::endl;
    Model::all_labels.push_back(line);
  }
}

void Model::setNet(std::string configuration, std::string model) {
  net = cv::dnn::readNetFromDarknet(configuration, model);
}

cv::Mat Model::predict(cv::Mat input_image) {
  int frame_height = input_image.cols;
  int frame_width = input_image.rows;
  cv::Mat blob;
  cv::dnn::blobFromImage(input_image, blob, 1./255, cv::Size(frame_width, frame_height), \
                            cv::Scalar(0, 0, 0), true, false);
  net.setInput(blob);
  cv::Mat output = net.forward();
  return output;
}
