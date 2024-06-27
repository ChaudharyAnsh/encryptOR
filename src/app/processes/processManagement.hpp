#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include <memory>
#include <queue>

#include "task.hpp"

class processManagement {
   public:
    processManagement();
    bool submitToQueue(std::unique_ptr<Task> task);
    void executeTasks();

   private:
    std::queue<std::unique_ptr<Task>> taskQueue;
};

#endif