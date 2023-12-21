#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:
    ThreadPool(std::size_t num_threads = std::thread::hardware_concurrency());
    ~ThreadPool();

    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(std::forward<F>(f)(std::forward<Args>(args)...))>;

private:
    std::queue<std::function<void()>> _tasks;
    std::vector<std::thread>          _workers;

    std::mutex              _mtx;
    std::condition_variable _cv;
    std::atomic<bool>       _stop{false};
};

#include "thread_pool.inl"
