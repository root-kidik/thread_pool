#include <iostream>

#include "thread_pool.hpp"

int foo(int a, int b)
{
    return a + b;
}

int main()
{
    ThreadPool tp;
    auto       res = tp.enqueue(foo, 1, 2);
    std::cout << res.get() << "\n";
}
