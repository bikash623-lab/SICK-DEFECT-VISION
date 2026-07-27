#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T> // T means any type: cv::Mat, int, etc.
class ThreadSafeQueue {
public:
    //Thread 1 calls push() to add a frame
    void push(T item){
        std::lock_guard<std::mutex> lock(mutex_); //lock
        queue_.push(item); // add item
        cv_.notify_one(); // wake up thread 2 if sleeping
    } // Lock automatically released here

    // Thread 2 calls waitAndPop() to get a frame
    //Block (sleeps) untill an item is available
    T waitAndPop(){
        std::unique_lock<std::mutex> lock(mutex_);
        //sleep until queue is not empty
        cv_.wait(lock, [this] {return !queue_.empty();});
        T item = queue_.front();
        queue_.pop();
        return item;
    }
    bool empty() const{
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }
private:
    std::queue<T> queue_; //actuall storage
    mutable std::mutex mutex_; // the lock
    std::condition_variable cv_; // for sleeping/waking
}