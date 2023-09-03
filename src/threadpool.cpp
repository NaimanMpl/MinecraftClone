#include "threadpool.h"

ThreadPool::ThreadPool(size_t threadsSize) {
    this->stop = false;
    this->threadsSize = threadsSize;
    startThreads(threadsSize);
}

ThreadPool::~ThreadPool() {
    std::unique_lock<std::mutex> lock(queueMutex);
    stop = true;
    conditionVariable.notify_all();
    for (std::thread& thread : threads) {
        thread.join();
    }
}

void ThreadPool::startThreads(size_t threadsSize) {
    for (size_t i = 0; i < threadsSize; i++) {
        threads.emplace_back([this] {
            while (true) {
                std::function<void()> task;
                
                std::unique_lock<std::mutex> lock(queueMutex);
                conditionVariable.wait(lock, [this] { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) {
                    return;
                }
                task = std::move(tasks.front());
                tasks.pop();

                task();
                currentTasksSize--;
            }
        });
    }
}

size_t ThreadPool::getThreadsSize() {
    return this->threadsSize;
}

unsigned int ThreadPool::getCurrentTasksSize() {
    return this->currentTasksSize;
}