#ifndef INCLUDE_TRACK_HPP_
#define INCLUDE_TRACK_HPP_

#include <vector>
#include <opencv2/core/types.hpp>

class Tracker{
    public:
    std::vector trackBoxCenters(std::vector<cv::Point> centroids);
};


#endif  // INCLUDE_TRACK_HPP_
