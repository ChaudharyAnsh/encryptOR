#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include <memory>
#include <queue>

#include "../threading/threadPool.cpp"
#include "task.hpp"

#define NUM_THREAD 8

class processManagement {
   public:
    processManagement();
    bool submitToQueue(std::shared_ptr<Task> task);
    void handover();

   private:
    threadPool pool = threadPool(NUM_THREAD);
};

#endif