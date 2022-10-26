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
    // std::cout << line << std::endl;
    Model::all_labels.push_back(line);
  }
}

void Model::setNet(std::string configuration, std::string model) {
  net = cv::dnn::readNetFromDarknet(configuration, model);
}

std::vector<cv::Mat> Model::predict(cv::Mat input_image) {
  int frame_height = input_image.cols;
  int frame_width = input_image.rows;
  cv::Mat blob;
  cv::dnn::blobFromImage(input_image, blob, 1. / 255,
                         cv::Size(416, 416),
                         cv::Scalar(0, 0, 0), true, false);
  net.setInput(blob);
  std::vector<cv::Mat> outs;
  net.forward(outs, getOutputsNames());
  return outs;
}

std::vector<std::string> Model::getOutputsNames() {
    static std::vector<std::string> names;
    if (names.empty()) {
        // Get the indices of the output layers, i.e. the layers
        // with unconnected outputs
        std::vector<int> outLayers = net.getUnconnectedOutLayers();
        // Get the names of all the layers in the network
        std::vector<std::string> layersNames = net.getLayerNames();
        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
        names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}
