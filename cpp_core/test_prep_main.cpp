#include "preprocessor.hpp"
#include <iostream>

int main(){
    //load the image 
    cv::Mat image = cv::imread("data/Photo.jpg");
    

    if(image.empty()){
        std::cerr <<"Failed: could not load images."<< std::endl;
        return 1;
    }

    std::cout << "Original size:" <<image.cols << "x" << image.rows << std::endl;

    //test resize
    ResizePreprocessor resizer(640, 640);
    cv::Mat resized = resizer.process(image);
    std::cout <<"After resize:"<<resized.cols << "x" << resized.rows <<std::endl;

    //Normalize Preprocessor
    NormalizePreprocessor normalizer;
    cv::Mat normalized = normalizer.process(resized);
    std::cout <<"After normalize: "<< normalized.cols << "x" << normalized.rows << std::endl;


    // test DenoisePreprocessoer
    DenoisePreprocessor denoiser;
    cv::Mat denoised = denoiser.process(normalized);
    std::cout <<"After denoise:"
    <<denoised.cols <<"x"<<denoised.rows << std::endl;


    // test EdgePreprocessor
    EdgePreprocessor edger;
    cv::Mat edges = edger.process(denoised);
    std::cout << "After edge detection:" << edges.cols << "x" << edges.rows <<std::endl;

    std::cout <<"All Preprocessor passed" <<std::endl;
    return 0;
}