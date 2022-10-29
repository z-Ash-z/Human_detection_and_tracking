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
 * @brief Tracks humans, draws bounding boxes around them and performs the perspective transform
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <track.hpp>

HumanTracker::HumanTracker() : _focal_length{0}, _average_height{0} {}

HumanTracker::~HumanTracker() {}

void HumanTracker::setFocalLength(double new_f) { _focal_length = new_f; }

void HumanTracker::setAvgHeight(double new_height) {
  _average_height = new_height;
}

const double HumanTracker::getFocalLength() {
  return _focal_length;
}

const double HumanTracker::getAvgHeight() {
  return _average_height;
}

const std::vector<cv::Point3d> HumanTracker::getRobotPerspective(
    const std::vector<cv::Rect> &boxes, const std::vector<int> &indices) {
  std::vector<cv::Point3d> world_coordinates;
  for (auto index : indices) {
    cv::Point3d coordinate;
    cv::Rect human = boxes.at(index);
    cv::Point centroid;
    centroid.x = (human.x + (human.width / 2));
    centroid.y = (human.y + (human.height / 2));
    double depth = _focal_length * _average_height / centroid.x;
    double width = centroid.y * depth / _focal_length;
    coordinate.x = _average_height;
    coordinate.y = width;
    coordinate.z = depth;
    world_coordinates.push_back(coordinate);
    std::cout << "x: " << coordinate.x << ", y: " << coordinate.y
              << ", z: " << coordinate.z << std::endl;
  }
  return world_coordinates;
}
