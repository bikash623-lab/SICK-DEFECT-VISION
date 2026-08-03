#include "pipeline_runner.hpp"
#include <memory>
#include <iostream>

void PipelineRunner:: start(const std::string& image_dir){
    // Create simulator with image_dir
    simulator_ = std::make_unique<AcquisitionSimulator>(image_dir);

    // build preprocessing pipeline
    pipeline_.addstep(std::make_unique<ResizePreprocessor>(640, 640));
    pipeline_.addstep(std::make_unique<NormalizePreprocessor>());
    pipeline_.addstep(std::make_unique<DenoisePreprocessor>());
    pipeline_.addstep(std::make_unique<EdgePreprocessor>());

    running_ = true;

    // launch two threads simultaneously
    acquirer_ = std::thread(&PipelineRunner::acquireLoop,this);
    processor_ = std::thread(&PipelineRunner::processLoop, this);
    
    std::cout << "[runner] started both threads" << std:: endl;
}

void PipelineRunner::acquireLoop() {
    while (running_) {
        if (!simulator_->hasFrames()) break;
        cv::Mat frame = simulator_->nextFrame();
        if (!frame.empty()) {
            frame_queue_.push(frame);
        }
    }
}

void PipelineRunner::processLoop(){
    while (running_)
    {
        cv::Mat raw = frame_queue_.waitAndPop(); // wait for frame
        cv::Mat processed = pipeline_.run(raw); // preprocess
        result_queue_.push(processed); //push to quque
    }
    
}

bool PipelineRunner::getResult(cv::Mat& out) {
    return result_queue_.tryPop(out);
}


void PipelineRunner::stop() {
    running_ = false;
    frame_queue_.notify();    // wake up processLoop so it can exit
    if (acquirer_.joinable())  acquirer_.join();
    if (processor_.joinable()) processor_.join();
    std::cout << "[runner] stopped both threads" << std::endl;
}
