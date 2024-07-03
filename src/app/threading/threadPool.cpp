#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
using namespace std;
// #include "../processes/processManagement.hpp"
#include "../processes/task.hpp"

class threadPool {
   public:
    int numThreads;
    threadPool(int n) : numThreads(n), stop(false) {
        for (int i = 0; i < numThreads; i++) {
            threads.emplace_back([this] {
                while (1) {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this] {
                        return !taskQueue.empty() || stop;
                    });

                    if (stop) return;
                    auto run = std::move(taskQueue.front());
                    taskQueue.pop();
                    lock.unlock();
                    run();
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
    auto executeTask(F &&func, T &&task) -> future<int> {
        auto taskrun = make_shared<packaged_task<int()>>(bind(forward<F>(func),
                                                              forward<T>(task)));

        future<int> res = taskrun->get_future();
        unique_lock<mutex> lock(mtx);

        taskQueue.emplace([taskrun] -> void {
            (*taskrun)();
        });
		cout << taskQueue.size() << "\n";
        lock.unlock();
        cv.notify_one();
        return res;
    }

   private:
    std::queue<std::function<void()>> taskQueue;
    std::vector<std::thread> threads;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop;
};

// int main() {
//     IO io("../../.env");
//     Task tt = Task(io.getFileStream(), "../../test/a", Action::ENCRYPT, Cipher::OTPAD);
//     std::shared_ptr<Task> t = std::make_shared<Task>(tt);
// }