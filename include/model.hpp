#ifndef INCLUDE_MODEL_HPP
#define INCLUDE_MODEL_HPP

#include <opencv2/core/mat.hpp>
#include <vector>
#include <opencv2/opencv.hpp>

class Model {
    public:
    void preprocess();

    void trainModel();
    
    double predict();

    private:
    std::vector<cv::Mat> data;
};


#endif  // INCLUDE_MODEL_HPP_
