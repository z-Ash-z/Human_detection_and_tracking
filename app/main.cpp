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
#include <opencv2/highgui.hpp>
#include <track.hpp>

float min_confidence_score = 0.5;

int main() {
  Model model;
  model.setAllLabels("dependencies/coco.names");
  model.setNet("dependencies/yolov3.cfg", "dependencies/yolov3.weights");
  cv::VideoCapture cap(0);
  int count = 0;
  while (cap.isOpened()) {
    cv::Mat frame;
    bool isFrame = cap.read(frame);
    if (!isFrame) {
      break;
    }
    count++;
    if (count == 1) {
      break;
    }
    cv::Mat frame_outputs = model.predict(frame);
    // std::cout << frame_outputs.size() << '\n';

    // cv::Mat results(frame_outputs.size[0], frame_outputs.size[1], CV_32F,
    // frame_outputs.ptr<float>()); std::cout << results.size[0] << ' ' <<
    // results.size[1] << '\n';
    // // Run through all the predictions
    // for (int i = 0; i < results.rows; i++) {
    //   int class_id = int(results.at<float>(i, 1));
    //   float confidence = results.at<float>(i, 2);
    //   std::cout << confidence << '\n';
    //   // Check if the detection is over the min threshold and then draw bbox
    //   if (confidence > min_confidence_score){
    //       std::cout << "Yeayy!" << '\n';
    //       int bboxX = int(results.at<float>(i, 3) * frame.cols);
    //       int bboxY = int(results.at<float>(i, 4) * frame.rows);
    //       int bboxWidth = int(results.at<float>(i, 5) * frame.cols - bboxX);
    //       int bboxHeight = int(results.at<float>(i, 6) * frame.rows - bboxY);
    //       cv::rectangle(frame, cv::Point(bboxX, bboxY),
    //                     cv::Point(bboxX + bboxWidth, bboxY + bboxHeight),
    //                     cv::Scalar(0,0,255), 2);
    //       std::string class_name = model.all_labels[class_id-1];
    //       cv::putText(frame, class_name + " " +
    //       std::to_string(int(confidence*100)) +
    //               "%", cv::Point(bboxX, bboxY - 10),
    //               cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0,255,0), 2);
    //   }
    // }
    // cv::imshow("frame", frame);
    // int k = cv::waitKey(10);
    //   if (k == 113) {
    //       break;
    //   }
  }
  cap.release();
  cv::destroyAllWindows();
  return 0;
}
