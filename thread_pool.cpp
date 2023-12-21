#include "thread_pool.hpp"

ThreadPool::ThreadPool(size_t num_threads)
{
    _workers.reserve(num_threads);

    for (std::size_t i = 0; i < num_threads; ++i)
        _workers.emplace_back(
            [this]
            {
                for (;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(_mtx);
                        _cv.wait(lock, [this] { return _stop || !_tasks.empty(); });
                        if (_stop && _tasks.empty())
                            return;
                        task = std::move(_tasks.front());
                        _tasks.pop();
                    }

                    task();
                }
            });
}

ThreadPool::~ThreadPool()
{
    _stop = true;
    _cv.notify_all();
    for (std::thread& worker : _workers)
        worker.join();
}
