#include "pipeline_runner.hpp"
#include <memory>

void PipelineRunner:: start(const std::string& image_dir){
    simulator_ = AcquisitionSimulator(image_dir);
    pipeline_.addstep(std::make_unique<ResizePreprocessor>(640, 640));
    pipeline_.addstep(std::make_unique<NormalizePreprocessor>());
    pipeline_.addstep(std::make_unique<DenoisePreprocessor>());

    running_ = true;

    // launch two threads simultaneously
    acquirer_ = std::thread(&PipelineRunner::acquireLoop,this);
    processor_ = std::thread(&PipelineRunner::processLoop, this);
}

void PipelineRunner::acquireLoop(){
    while (running_)
    {
        cv::Mat frame = simulator_.nextFrame(); // read from disk
        frame_queue_.push(frame); // push to queue
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

void PipelineRunner::stop(){
    running_ = false;
    acquirer_.join(); // wait for Thread 1 to finish
    processor_.join(); // wait for Thread 2 to finish
}