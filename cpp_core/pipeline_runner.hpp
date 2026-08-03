#pragma once
#include "acquisition.hpp"
#include "pipeline.hpp"
#include "thread_safe_queue.hpp"
#include "thread"
#include "atomic"

class PipelineRunner{
public:
    PipelineRunner() = default;
    //start both threads
    void start(const std::string& image_dir); // starts both threads

    //stop both thread cleanly
    void stop();

    // Python calls this to get a processed frame
    bool getResult(cv::Mat& out);

    private:
        //Thread 1 - reads frame from simulator
        void acquireLoop();

        //Thread 2 - preprocesses frames
        void processLoop();

        std::unique_ptr<AcquisitionSimulator> simulator_;
        PreprocessingPipeline pipeline_;
        ThreadSafeQueue<cv::Mat> frame_queue_; //raw frame
        ThreadSafeQueue<cv::Mat> result_queue_; //processes frames
        std::atomic<bool> running_{false}; //thread-safe flag
        std::thread acquirer_; // thread 1
        std::thread processor_; // thread 2

};