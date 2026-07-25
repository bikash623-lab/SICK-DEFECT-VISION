#pragma once
#include "preprocessor.hpp"
#include <vector>
#include <memory>

class PreprocessingPipeline{
public:
    // add a preprocessing step to the action
    void addstep(std::unique_ptr<Preprocessor> step);

    //run all setps in order on the input image
    cv::Mat run(const cv::Mat& input);

    //numpy-compatible version for pybind11
    //(convert cv::Mat to numpy array)
    pybind11::array_t<uint8_t> runNumpy(pybind11::array_t<uint8_t> input);

    private:
        std::vector<std::unique_ptr<Preprocessor>> steps;
};