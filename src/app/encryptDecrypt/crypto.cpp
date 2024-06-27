#include "crypto.hpp"

#include "../fileHanding/readEnv.cpp"
#include "../processes/task.hpp"

int executeCrypto(std::unique_ptr<Task> task) {
    readEnv env;
    std::string key = env.getEnv();
    const size_t len = key.size();

    int ind = 0;
    char ch;

    while (task->fStream.get(ch)) {
        ch ^= key[ind];
        ind++, ind %= len;
        task->fStream.seekp(-1, std::ios::cur);
        task->fStream.put(ch);
    }
    task->fStream.close();
    return 0;
}