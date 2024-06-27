#include <iostream>

#include "../fileHanding/IO.hpp"
#include "../fileHanding/readEnv.cpp"
#include "../processes/processManagement.hpp"
#include "../processes/task.hpp"
#include "crypto.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage ./crypto <task_data>" << std::endl;
        return 1;
    }
    executeCrypto(Task::fromString(argv[1]));
    return 0;
}