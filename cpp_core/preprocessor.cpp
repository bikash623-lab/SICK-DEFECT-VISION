#include "preprocessor.hpp"
#include <iterator>

//ResizePreprocessor
ResizePreprocessor::ResizePreprocessor(int width, int height){
    width_ = width;
    height_ = height;
}
cv::Mat ResizePreprocessor::process(const cv::Mat& input){
    cv::Mat resized;
    cv::resize(input, resized, cv::Size(width_, height_));
    return resized;
}
cv::Mat NormalizePreprocessor::process(const cv::Mat& input){
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // Applying Clahe
    cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(2.0, cv::Size(8,8));
    cv::Mat enhanced;
    clahe->apply(gray, enhanced);

    //Back to BGR
    cv::Mat result;
    cv::cvtColor(enhanced, result, cv::COLOR_GRAY2BGR);
    return result;
}

cv::Mat DenoisePreprocessor::process(const cv::Mat& input){
    cv::Mat blurred;
    cv::GaussianBlur(input, blurred, cv::Size(3,3), 0);
    return blurred;
}

cv::Mat EdgePreprocessor::process(const cv::Mat& input){
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::Mat edges;
    cv::Canny(gray, edges, 100, 200);
    cv::Mat result;
    cv::cvtColor(edges, result, cv::COLOR_GRAY2BGR);
    return result;
}