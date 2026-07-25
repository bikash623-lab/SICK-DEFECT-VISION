#include <iostream>
#include "acquisition.hpp"

int main(){
    AcquisitionSimulator sim("data");

    if(!sim.hasFrames()){
        std::cerr<<"Failed: no image found" << std::endl;
        return -1;
    }

    // grab frame and print ifno
    cv::Mat frame = sim.nextFrame();

    if(frame.empty()){
        std::cerr << "Failed: image is empty." << std::endl;    
        return 1;
    }
    std::cout <<"Success"<< std::endl;
    std::cout <<"Width:"<< frame.cols << std::endl;
    std::cout <<"Height:"<< frame.rows << std::endl;
    std::cout <<"Channels:"<<frame.channels()<< std::endl;
    return 0;
}