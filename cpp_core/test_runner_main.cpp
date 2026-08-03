#include <iostream>
#include "pipeline_runner.hpp"
#include <thread>
#include <chrono>

int main(){
    PipelineRunner runner;

    //starting the both threads
    runner.start("data");
    std::cout << "Pipeline runner started" << std::endl;
    std::cout << "Letting it run for 2 second..." << std::endl;

    // let it run for 2 second
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // collect result
    int count = 0;
    cv::Mat result;
    while (runner.getResult(result)){
        count++;
    }
    std::cout << "Processed " << count << "frames" << std::endl;

    // stop both threads cleanly
    runner.stop();
    std::cout << "Pipeline Runner Passed" << std::endl;
    return 0;
}