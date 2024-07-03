#include "crypto.hpp"

#include "../fileHanding/readEnv.cpp"
#include "../processes/task.hpp"
#include "string.h"

int executeBLOCK(std::shared_ptr<Task> task) {
    readEnv env;
    std::string key = env.getEnv();
    std::string replaceKey = "";
    const size_t len = key.size();

    int ind = 0;
    char ch;

    while (task->fStream.get(ch)) {
        if (task->action == Action::ENCRYPT)
            replaceKey.push_back(ch);
        ch ^= key[ind];
        if (task->action == Action::DECRYPT)
            replaceKey.push_back(ch);

        ind++, ind %= len;
        if (len == 0) key = replaceKey, replaceKey = "";
        task->fStream.seekp(-1, std::ios::cur);
        task->fStream.put(ch);
    }
    task->fStream.close();
    return 0;
}

int executeCAESAR(std::shared_ptr<Task> task) {
    readEnv env;
    std::string key = env.getEnv();
    const int offset = key[0];
    char ch;
    while (task->fStream.get(ch)) {
        ch = (ch + offset) % 256;
        task->fStream.seekp(-1, std::ios::cur);
        task->fStream.put(ch);
    }
    task->fStream.close();
    return 0;
}

int executeOTPAD(std::shared_ptr<Task> task) {
    readEnv env;
    std::string key = env.getEnv();
    // std::cout << key << " ";
    // std::cout.flush();
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

int executeVIGNERE(std::shared_ptr<Task> task) {
    readEnv env;
    std::string key = env.getEnv();
    const size_t len = key.size();
    int offset;
    char ch;

    if (task->action == Action::ENCRYPT)
        offset = 0;
    else
        offset = 256;

    while (task->fStream.get(ch)) {
        ch = key[ch + offset];
        task->fStream.seekp(-1, std::ios::cur);
        task->fStream.put(ch);
    }
    task->fStream.close();
    return 0;
}