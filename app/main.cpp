/**
 * @file main.cpp
 * @author Aneesh Chodisetty (aneeshc@umd.edu)
 * @author Bhargav Kumar Soothram (bsoothra@umd.edu)
 * @author Joseph Pranadheer Reddy Katakam (jkatak@umd.edu)
 * @brief Driver file for module execution
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <model.hpp>
#include <track.hpp>

int main() {
  Model model;
  model.setAllLabels("./dependencies/coco.names");
  model.setNet("./dependencies/yolov3.cfg", "./dependencies/yolov3.weights");
  model.setConfidenceThresh(0.5);
  model.setNMSThreshold(0.4);

  HumanTracker humans;
  humans.setFocalLength(25);
  humans.setAvgHeight(170);
  cv::VideoCapture cap(0);

  while (cap.isOpened()) {
    cv::Mat frame;
    bool isFrame = cap.read(frame);
    if (!isFrame) {
      break;
    }

    std::vector<cv::Mat> frame_outputs = model.predict(frame);

    model.postProcess(frame, frame_outputs);
    model.setNMSIndices();

    std::vector<cv::Rect> all_boxes = model.getBoxes();
    std::vector<int> nms_indices = model.getNMSIndices();

    // check to see if humans are detected
    if (static_cast<int>(nms_indices.size()) != 0) {
      // print the number of detections
      std::cout << "\nHumans Detected: " << static_cast<int>(nms_indices.size()) << std::endl;

      // transforming to robot coordinates
      humans.getRobotPerspective(all_boxes, nms_indices);

      // track the detected humans
      frame = model.drawBoxes(&frame);
      cv::imshow("Boxes", frame);
    } else {
      std::cout << std::endl << "No Humans were detected!" << std::endl;
    }

    cv::waitKey(1);
  }
  cap.release();
  cv::destroyAllWindows();

  return 0;
}
