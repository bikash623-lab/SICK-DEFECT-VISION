#include "pipeline.hpp"

void PreprocessingPipeline::addstep(std::unique_ptr<Preprocessor> step){
    //std::move transfer ownership from caller to steps_ vector
    steps_.push_back(std::move(step));

}

cv::Mat PreprocessingPipeline::run(const cv::Mat& input){
    // start with a copy of the original image
    cv::Mat result = input.clone();

    //pass image through each step in order
    //output of step 1 becomes input of step 2 and so on
    for(auto& step: steps_){
        result = step->process(result);
    }
    return result; // fully preprocessed image
    
}