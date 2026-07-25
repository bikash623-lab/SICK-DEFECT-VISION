#pragma once
#include <opencv2/opencv.hpp>

//Base class every preprocessing step inherits from here
class Preprocessor{
public:
    virtual ~Preprocessor() = default;

    //It takes image in, return processed image out
    virtual cv::Mat process(const cv::Mat& input) = 0;
};

class ResizePreprocessor : public Preprocessor{
public:
    ResizePreprocessor(int width, int height);
    cv::Mat process(const cv::Mat& input) override;
private:
    int width_, height_;
};


class NormalizePreprocessor : public Preprocessor{
public:
    cv::Mat process(const cv::Mat& input) override;

};

class DenoisePreprocessor : public Preprocessor{
public:
    cv::Mat process(const cv::Mat& input) override;

};

class EdgePreprocessor : public Preprocessor{
public:
    cv::Mat process(const cv::Mat& input) override;
};

