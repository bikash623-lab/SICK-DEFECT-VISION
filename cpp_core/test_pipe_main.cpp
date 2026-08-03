#include <iostream>
#include "pipeline.hpp"
#include "preprocessor.hpp"

int main(){
    cv::Mat image = cv::imread("data/Photo.jpg");

    PreprocessingPipeline pipeline;
    pipeline.addstep(std::make_unique<ResizePreprocessor>(640, 640));
    pipeline.addstep(std::make_unique<NormalizePreprocessor>());
    pipeline.addstep(std::make_unique<DenoisePreprocessor>());
    pipeline.addstep(std::make_unique<EdgePreprocessor>());

    cv::Mat result = pipeline.run(image);

    std::cout <<"Input:" <<image.cols <<"x"<<image.rows<<std::endl;
    std::cout <<"Output:" <<result.cols <<"x"<<result.rows<<std::endl;
    std::cout <<"Pipeline Passes" <<std::endl;

    return 0;


}