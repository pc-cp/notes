#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <deque>

class ThreadPool {
    public:
        using Task = std::function<void ()>;

        ThreadPool() : mutex_(), cv_(), running_(false) {

        }
        ~ThreadPool() {
            if(running_) 
                stop();
        }

        void start(int num) {
            running_ = true;
            for(int i = 0; i < num; ++i) {
                threads_.push_back(std::make_shared<std::thread>(std::bind(&ThreadPool::runInThread, this)));
            }
        }

        void stop() {
            running_ = false;
            cv_.notify_all();
            for(int i = 0; i < threads_.size(); ++i) {
                threads_[i]->join();
            }
        }

        void run(const Task& task) {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push_back(task);
            cv_.notify_one();
        }

        Task take() {
            std::unique_lock<std::mutex> lock(mutex_);
            while(queue_.empty() && running_) {
                cv_.wait(lock);
            }

            Task task;
            if(!queue_.empty()) {
                task = queue_.front();
                queue_.pop_front();
            }
            return task;
        }

    private:
        void runInThread() {
            while(running_) {
                Task task(take());
                if(task) {
                    task();
                }
            }
        }

        std::condition_variable cv_;
        std::mutex mutex_;

        std::vector<std::shared_ptr<std::thread>> threads_;
        std::deque<Task> queue_;
        bool running_;
};

#include <unistd.h>
#include <syscall.h>

void print() {
    printf("tid = %d\n", static_cast<pid_t>(::syscall(SYS_gettid)));
}

int main() {
    ThreadPool pool;

    pool.start(2);

    for(int i = 0; i < 10; ++i) {
        pool.run(print);
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));
}