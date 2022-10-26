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

#include <iostream>
#include <model.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <track.hpp>

float min_confidence_score = 0.5;
float nms_threshold = 0.4;

int main() {
  Model model;
  model.setAllLabels("dependencies/coco.names");
  model.setNet("dependencies/yolov3.cfg", "dependencies/yolov3.weights");


  cv::VideoCapture cap(0);
  // int count = 0;
  // while (cap.isOpened()) {
  //   cv::Mat frame;
  //   bool isFrame = cap.read(frame);
  //   if (!isFrame) {
  //     break;
  //   }
    // count++;
    // if (count == 10) {
    //   break;
    // }
    // cap.release();
    cv::Mat frame(cv::imread("data/aneesh.jpeg"));
    std::vector<cv::Mat> frame_outputs = model.predict(frame);
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    for (size_t i = 0; i < frame_outputs.size(); ++i) {
      float* data = reinterpret_cast<float*>(frame_outputs[i].data);
      for (int j = 0; j < frame_outputs[i].rows; ++j, data += frame_outputs[i].cols) {
        cv::Mat scores = frame_outputs[i].row(j).colRange(5, frame_outputs[i].cols);
        cv::Point classIdPoint;
        double confidence;
        cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
        if ((confidence > min_confidence_score) && (classIdPoint.x == 0)) {
          int centerX = static_cast<int>(data[0] * frame.cols);
          int centerY = static_cast<int>(data[1] * frame.rows);
          int width = static_cast<int>(data[2] * frame.cols);
          int height = static_cast<int>(data[3] * frame.rows);
          int left = centerX - width / 2;
          int top = centerY - height / 2;
          classIds.push_back(classIdPoint.x);
          confidences.push_back(static_cast<float>(confidence));
          boxes.push_back(cv::Rect(left, top, width, height));
        }
      }
    }
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, min_confidence_score, nms_threshold, indices);

    HumanTracker Humans;
    Humans.getRobotPerspective(boxes, indices);

    // for (auto index : indices) {
    //   std::cout << index << std::endl;
    //   auto box = boxes.at(index);
    //   cv::rectangle(frame, cv::Point(box.x, box.y), cv::Point(box.x + box.width, box.y + box.height), cv::Scalar(255, 178, 50), 3);
    // }
    // cv::imshow("Boxes", frame);
    // cv::waitKey(0);
  // }
  
  cv::destroyAllWindows();
  return 0;
}
