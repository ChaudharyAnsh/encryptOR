#include "crypto.hpp"

#include <chrono>
#include <thread>
#include <vector>

#include "../fileHanding/readEnv.cpp"
#include "../processes/task.hpp"
#include "string.h"
using namespace std;
int executeBLOCK(std::shared_ptr<Task> task) {
    std::string key = task->keybuf;
    std::string replaceKey = "";
    std::string s;
    std::fstream f = std::move(task->fStream);
    const size_t len = key.size();

    int ind = 0;
    char ch;

    while (f.get(ch)) {
        if (task->action == Action::ENCRYPT)
            replaceKey.push_back(ch);
        if (task->action == Action::DECRYPT)
            replaceKey.push_back(ch);
        s.push_back(ch ^= key[ind]);
        ind++, ind %= len;
        if (len == 0) key = replaceKey, replaceKey = "";
    }
    f.clear();
    f.seekp(0, ios::beg);
    for (auto &ch : s) f.put(ch);
    f.close();
    return 0;
}

int executeCAESAR(std::shared_ptr<Task> task) {
    readEnv env;
    std::string key = env.getEnv();
    std::string s;
    std::fstream f = std::move(task->fStream);

    const int offset = key[0];
    char ch;

    while (f.get(ch)) s.push_back((ch + offset) % 256);
    f.clear();
    f.seekp(0, ios::beg);
    for (auto &ch : s) f.put(ch);
    f.close();
    return 0;
}

int executeOTPAD(std::shared_ptr<Task> task) {
    std::string key = task->keybuf;
    const size_t len = key.size();
    std::string s;
    std::fstream f = std::move(task->fStream);

    int ind = 0;
    char ch;

    while (f.get(ch)) {
        s.push_back(ch ^ key[ind]);
        ind++, ind %= len;
    }

    f.clear();
    f.seekp(0, ios::beg);
    for (auto &ch : s) f.put(ch);
    f.close();
    return 0;
}

int executeVIGNERE(std::shared_ptr<Task> task) {
    readEnv env;
    std::string key = env.getEnv();
    std::string s;
    std::fstream f = std::move(task->fStream);
    const size_t len = key.size();

    int offset;
    char ch;

    if (task->action == Action::ENCRYPT)
        offset = 0;
    else
        offset = 256;

    while (f.get(ch)) s.push_back(key[ch + offset]);
    f.clear();
    f.seekp(0, ios::beg);
    for (auto &ch : s) f.put(ch);
    f.close();
    return 0;
}