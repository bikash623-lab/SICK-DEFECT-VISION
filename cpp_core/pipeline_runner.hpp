#pragma once
#include "acquisition.hpp"
#include "pipeline.hpp"
#include "thread_safe_queue.hpp"
#include "thread"
#include "atomic"

class PipelineRunner{
public:
    //start both threads
    void start(const std::string& image_dir);

    //stop both thread cleanly
    void stop();

    // Python calls this to get a processed frame
    bool getResult(cv::Mat& out);

    private:
        //Thread 1 - reads frame from simulator
        void acquireLoop();

        //Thread 2 - preprocesses frames
        void processLoop();

        AcquisitionSimulator simulator_;
        PreprocessingPipeline pipeline_;
        ThreadSafeQueue<cv::Mat> frame_queue_; //raw frame
        ThreadSafeQueue<cv::Mat> result_queue_; //processes frames
        std::atomic<bool> running_{false};
        std::thread acquirer_;
        std::thread processor_;

};