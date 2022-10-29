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
  model.setAllLabels("dependencies/coco.names");
  model.setNet("dependencies/yolov3.cfg", "dependencies/yolov3.weights");
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

    // cv::Mat frame(cv::imread("data/aneesh.jpeg"));
    std::vector<cv::Mat> frame_outputs = model.predict(frame);

    model.postProcess(frame, frame_outputs);
    model.setNMSIndices();  // Need to write a small code snippet to check if at
                            // all humans are detected in a given frame
                            // (len(nms_indices) = 0)

    std::vector<cv::Rect> all_boxes = model.getBoxes();
    std::vector<int> nms_indices = model.getNMSIndices();

    humans.getRobotPerspective(all_boxes, nms_indices);

    frame = model.drawBoxes(&frame);
    cv::imshow("Boxes", frame);
    cv::waitKey(1);
  }
  cap.release();
  cv::destroyAllWindows();

  return 0;
}
