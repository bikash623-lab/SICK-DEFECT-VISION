#pragma once
#include "preprocessor.hpp"
#include <vector>
#include <memory>

class PreprocessingPipeline{
public:
    // add a step to the chain
    // unique_ptr means pipeline takes ownership of the step
    void addstep(std::unique_ptr<Preprocessor> step);

    // run image through All steps in order
    cv::Mat run(const cv::Mat& input);

private:
    // vector of steps - each is a unique_ptr to a Preprocessor
    std::vector<std::unique_ptr<Preprocessor>> steps_;
};