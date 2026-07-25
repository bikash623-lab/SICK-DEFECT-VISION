#include "acquisition.hpp"
#include <iostream>
#include <string>

AcquisitionSimulator:: AcquisitionSimulator(const std::string& image_dir){
    // Load all jpg and png images from folder
    cv:: glob(image_dir + "/*.jpg", image_path_, false);

    std::vector<std::string> pngs;
    cv::glob(image_dir + "/*.png", pngs, false);

    // combine jpg and png paths
    image_path_.insert(image_path_.end(), pngs.begin(), pngs.end());


    if(image_path_.empty()){
        std::cerr << "Aquisition no images found in: " 
        << image_dir << std::endl;
    }
    else{
        std::cout << "Aquisition loaded" << image_path_.size() 
        << "image from: " << image_dir << std:: endl;
    }
    current_index_ = 0;
}
cv::Mat AcquisitionSimulator:: nextFrame(){
    if(image_path_.empty()){
        return cv::Mat();
    }

    // read current image 
    cv::Mat frame = cv::imread(image_path_[current_index_]);

    if(frame.empty()){
        std::cerr << "Aquisition falied to load: " << image_path_[current_index_] << std::endl;
    }

    // move to next, wrap around at end
    current_index_ = (current_index_ + 1) % image_path_.size();
    
    return frame;
}

bool AcquisitionSimulator:: hasFrames() const{
    return !image_path_.empty();
}

void AcquisitionSimulator::reset(){
    current_index_ = 0;
}