template <class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<decltype(std::forward<F>(f)(std::forward<Args>(args)...))>
{
    using return_type = decltype(std::forward<F>(f)(std::forward<Args>(args)...));

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();

    {
        std::unique_lock<std::mutex> lock(_mtx);
        _tasks.emplace([task]() { (*task)(); });
    }

    _cv.notify_one();
    return res;
}
