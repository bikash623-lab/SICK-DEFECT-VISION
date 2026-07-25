#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>


class AcquisitionSimulator {
public:
    // Constructor to pass the folder path of images.
    AcquisitionSimulator(const std::string& image_dir);

    // Returns next frame as cv:: Mat
    cv::Mat nextFrame();

    // True if images are available 
    bool hasFrames() const;

    // Reset back to first image
    void reset();


private:
    std::vector<std::string> image_path_;
    size_t current_index_;
};


