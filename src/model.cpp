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

Model::Model() : _min_confidence_score{0}, _nms_threshold{0} {}

Model::~Model() {}

void Model::setAllLabels(std::string file_path) {
  std::ifstream input_stream(file_path.c_str());
  std::string line;
  while (getline(input_stream, line)) {
    Model::_all_labels.push_back(line);
  }
}

void Model::setNet(std::string configuration, std::string model) {
  _net = cv::dnn::readNetFromDarknet(configuration, model);
}

std::vector<std::string> Model::getOutputsNames() {
  static std::vector<std::string> names;
  if (names.empty()) {
    std::vector<int> outLayers =
        _net.getUnconnectedOutLayers();  // Get the indices of the output layers
    std::vector<std::string> layersNames =
        _net.getLayerNames();  // Get the names of all the layers in the network
    names.resize(
        outLayers.size());  // Get the names of the output layers in names
    for (size_t i = 0; i < outLayers.size(); ++i)
      names[i] = layersNames[outLayers[i] - 1];
  }
  return names;
}

std::vector<cv::Mat> Model::predict(cv::Mat input_image) {
  cv::Mat blob;
  cv::dnn::blobFromImage(input_image, blob, 1. / 255, cv::Size(416, 416),
                         cv::Scalar(0, 0, 0), true, false);
  _net.setInput(blob);
  std::vector<cv::Mat> outs;
  _net.forward(outs, getOutputsNames());
  return outs;
}

void Model::setConfidenceThresh(double conf_thresh) {
  _min_confidence_score = conf_thresh;
}

void Model::setNMSThreshold(double nms_thresh) { _nms_threshold = nms_thresh; }

void Model::postProcess(const cv::Mat &frame,
                        const std::vector<cv::Mat> &dnn_outs) {
  _classIds.clear();
  _confidences.clear();
  _boxes.clear();
  for (size_t i = 0; i < dnn_outs.size(); ++i) {
    float *data = reinterpret_cast<float *>(dnn_outs[i].data);
    for (int j = 0; j < dnn_outs[i].rows; ++j, data += dnn_outs[i].cols) {
      cv::Mat scores = dnn_outs[i].row(j).colRange(5, dnn_outs[i].cols);
      cv::Point classIdPoint;
      double confidence;
      cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
      if ((confidence > _min_confidence_score) && (classIdPoint.x == 0)) {
        int centerX = static_cast<int>(data[0] * frame.cols);
        int centerY = static_cast<int>(data[1] * frame.rows);
        int width = static_cast<int>(data[2] * frame.cols);
        int height = static_cast<int>(data[3] * frame.rows);
        int left = centerX - width / 2;
        int top = centerY - height / 2;
        _classIds.push_back(classIdPoint.x);
        _confidences.push_back(static_cast<float>(confidence));
        _boxes.push_back(cv::Rect(left, top, width, height));
      }
    }
  }
}

std::vector<cv::Rect> Model::getBoxes() { return _boxes; }

void Model::setNMSIndices() {
  cv::dnn::NMSBoxes(_boxes, _confidences, _min_confidence_score, _nms_threshold,
                    _nms_indices);
}

std::vector<int> Model::getNMSIndices() { return _nms_indices; }

cv::Mat Model::drawBoxes(cv::Mat *frame) {
  for (auto index : _nms_indices) {
    auto box = _boxes.at(index);
    double conf = _confidences.at(index);
    int classID = _classIds.at(index);

    int left{box.x};
    int top{box.y};
    int right{box.x + box.width};
    int bottom{box.y + box.height};
    cv::rectangle(*frame, cv::Point(left, top), cv::Point(right, bottom),
                  cv::Scalar(255, 178, 50), 3);

    // Draw the predicted bounding box
    // Get the label for the class name and its confidence
    std::string label = cv::format("%.2f", conf);
    if (!_all_labels.empty()) {
      CV_Assert(classID < static_cast<int>(_all_labels.size()));
      label = _all_labels[classID] + ":" + label;
    }
    // Display the label at the top of the bounding box
    int baseLine;
    cv::Size labelSize =
        getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    top = cv::max(top, labelSize.height);
    cv::rectangle(
        *frame, cv::Point(left, top - round(1.5 * labelSize.height)),
        cv::Point(left + round(1.5 * labelSize.width), top + baseLine),
        cv::Scalar(255, 255, 255), cv::FILLED);
    cv::putText(*frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX,
                0.75, cv::Scalar(0, 0, 0), 1);
  }
  return *frame;
}
