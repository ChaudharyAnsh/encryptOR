#include <iostream>

#include "../fileHanding/IO.hpp"
#include "../fileHanding/readEnv.cpp"
#include "../processes/processManagement.hpp"
#include "../processes/task.hpp"
#include "crypto.hpp"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage ./crypto (file_name) (encrypt/decrypt) (MODE)\n";
        return 1;
    }
    // executeBLOCK(Task::fromString(argv[1], argv[2], argv[3]));
    return 0;
}