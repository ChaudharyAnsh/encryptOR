#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "../processes/task.hpp"

class threadPool {
   public:
    int numThreads;
    threadPool(int n) : numThreads(n), stop(false) {
        for (int i = 0; i < numThreads; i++) {
            threads.emplace_back([this] {
                while ((!stop) || (stop && !taskQueue.empty())) {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this] {
                        return (!taskQueue.empty() || stop);
                    });

                    if (!taskQueue.empty()) {
                        auto run = std::move(taskQueue.front());
                        taskQueue.pop();
                        lock.unlock();
                        run();
                    }
                }
            });
        }
    }

    ~threadPool() {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
        lock.unlock();
        cv.notify_all();

        for (auto &thread : threads) {
            thread.join();
        }
    }

    template <class F, class T>
    auto executeTask(F &&func, T &&task) -> void {
        auto taskrun = std::make_shared<std::packaged_task<int()>>(std::bind(forward<F>(func),
                                                                             forward<T>(task)));

        std::future<int> res = taskrun->get_future();
        std::unique_lock<std::mutex> lock(mtx);

        taskQueue.emplace([taskrun] -> void {
            (*taskrun)();
        });
        lock.unlock();
        cv.notify_one();
    }

   private:
    std::condition_variable cv;
    std::mutex mtx;
    std::atomic_bool stop;
    std::queue<std::function<void()>> taskQueue;
    std::vector<std::thread> threads;
};
