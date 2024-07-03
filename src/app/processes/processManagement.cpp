#include "processManagement.hpp"

#include <sys/wait.h>

#include <cstring>
#include <iostream>
#include <vector>

#include "../encryptDecrypt/crypto.hpp"

processManagement::processManagement() {}
bool processManagement::submitToQueue(std::shared_ptr<Task> task) {
    std::function<int(std::shared_ptr<Task>)> func;
    switch (task->cipher) {
        case Cipher::CAESAR:
            func = executeCAESAR;
            break;
        case Cipher::OTPAD:
            func = executeOTPAD;
            break;
        case Cipher::BLOCK:
            func = executeBLOCK;
            break;
        default:
            func = executeVIGNERE;
            break;
    }
    future<int> res = pool.executeTask(func, task);
    return true;
}

void processManagement::handover() {
    // while (!taskQueue.empty()) {
    //     std::shared_ptr<Task> currentTask = std::move(taskQueue.front());
    //     taskQueue.pop();
    //     std::cout << "Executing task " << currentTask->toString() << std::endl;
    //     switch (currentTask->cipher) {
    //         case Cipher::CAESAR:
    //             executeCAESAR(std::move(currentTask));
    //         case Cipher::OTPAD:
    //             executeOTPAD(std::move(currentTask));
    //             break;
    //         case Cipher::BLOCK:
    //             executeBLOCK(std::move(currentTask));
    //             break;
    //         default:
    //             executeVIGNERE(std::move(currentTask));
    //             break;
    //     }
    // }
}