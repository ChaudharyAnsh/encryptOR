#include "processManagement.hpp"

#include <sys/wait.h>

#include <cstring>
#include <iostream>

#include "../encryptDecrypt/crypto.hpp"

processManagement::processManagement() {}
bool processManagement::submitToQueue(std::unique_ptr<Task> task) {
    taskQueue.push(std::move(task));
    return true;
}

void processManagement::executeTasks() {
    while (!taskQueue.empty()) {
        std::unique_ptr<Task> currentTask = std::move(taskQueue.front());
        taskQueue.pop();
        std::cout << "Executing task " << currentTask->toString() << std::endl;
        executeCrypto(std::move(currentTask));
    }
}