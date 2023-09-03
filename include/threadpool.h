#ifndef THREAD_POOL_CLASS_H
#define THREAD_POOL_CLASS_H

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
    private:
        bool stop;
        size_t threadsSize;
        unsigned int currentTasksSize;
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> tasks;
        std::mutex queueMutex;
        std::condition_variable conditionVariable;
        void startThreads(size_t threadsSize);
    public:
        ThreadPool() = default;
        ThreadPool(size_t threadsSize);
        ~ThreadPool();
        
        template<class F>
        void enqueue(F&& f) {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace(std::forward<F>(f));
            conditionVariable.notify_one();
            currentTasksSize++;
        }
        size_t getThreadsSize();
        unsigned int getCurrentTasksSize();

};

#endif