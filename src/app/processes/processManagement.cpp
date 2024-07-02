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
        switch (currentTask->cipher) {
            case Cipher::CAESAR:
                executeCAESAR(std::move(currentTask));
                break;
            case Cipher::OTPAD:
                executeOTPAD(std::move(currentTask));
                break;
            case Cipher::BLOCK:
                executeBLOCK(std::move(currentTask));
                break;
            default:
                executeVIGNERE(std::move(currentTask));
                break;
        }
    }
}