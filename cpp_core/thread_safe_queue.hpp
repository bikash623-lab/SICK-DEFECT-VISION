#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
public:
    //add item to back of queue
    //wakes up any sleeping consumer
    void push(T item);

    //remove and return item from front
    //block (sleeps) until item is available
    T waitAndPop();

    //non-blocking pop - retirn false if empty
    bool tryPop(T& item);

    bool empty() const;

    size_t size() const;

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
}