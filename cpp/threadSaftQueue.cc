#include <iostream>
#include <queue>
#include <condition_variable>
#include <mutex>

// using namespace std;

class MyQueue {

    void push(int val) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(val);
        if(queue_.size() == 1) {
            cv_.notify_one();
        }
    }

    void pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        while(queue_.empty()) {
            cv_.wait(lock);
        }
        queue_.pop();
    }

    int top() {
        std::unique_lock<std::mutex> lock(mutex_);
        while(queue_.empty()) {
            cv_.wait(lock);
        }
        int val = queue_.front();
        return val;
    }

private:
    std::queue<int> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
};