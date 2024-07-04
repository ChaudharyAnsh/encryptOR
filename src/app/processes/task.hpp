#ifndef TASK_HPP
#define TASK_HPP
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "../fileHanding/IO.hpp"

enum class Action { ENCRYPT,
                    DECRYPT };

enum class Cipher { BLOCK,
                    OTPAD,
                    CAESAR,
                    VIGNERE
};

struct Task {
    std::string filePath;
    std::fstream fStream;
    std::string keybuf;

    Action action;
    Cipher cipher;

    Task(std::fstream &&stream, std::string filePath, std::string key, Action act, Cipher ciph)
        : fStream(std::move(stream)), filePath(filePath), keybuf(key), action(act), cipher(ciph) {}

    std::string toString() {
        std::ostringstream oss;
        oss << filePath << ", "
            << (action == Action::ENCRYPT ? "oper=ENCRYPT, " : "oper=DECRYPT, ")
            << (cipher == Cipher::OTPAD    ? "method=OTP"
                : cipher == Cipher::BLOCK  ? "method=BLOCK"
                : cipher == Cipher::CAESAR ? "method=CAESAR"
                                           : "method=VIGNERE");
        return oss.str();
    }
};

#endif