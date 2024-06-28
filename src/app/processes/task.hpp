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
                    STREAM,
                    VIGNERE };

struct Task {
    std::string filePath;
    std::fstream fStream;
    Action action;
    Cipher cipher;

    Task(std::fstream &&stream, std::string filePath, Action act, Cipher ciph)
        : fStream(std::move(stream)), filePath(filePath), action(act), cipher(ciph) {}

    std::string toString() {
        std::ostringstream oss;
        oss << filePath << ", "
            << (action == Action::ENCRYPT ? "oper=ENCRYPT, " : "oper=DECRYPT, ")
            << (cipher == Cipher::OTPAD    ? "method=OTP"
                : cipher == Cipher::BLOCK  ? "method=BLOCK"
                : cipher == Cipher::CAESAR ? "method=CAESAR"
                : cipher == Cipher::STREAM ? "method=STREAM"
                                           : "method=VIGNERE");
        return oss.str();
    }

    static std::unique_ptr<Task> fromString(const std::string &taskData) {
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;
        std::string cipherStr;

        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr) && std::getline(iss, cipherStr)) {
            Action action = actionStr == "encrypt" ? Action::ENCRYPT : Action::DECRYPT;

            Cipher cipher = cipherStr == "otp"      ? Cipher::OTPAD
                            : cipherStr == "block"  ? Cipher::BLOCK
                            : cipherStr == "caesar" ? Cipher::CAESAR
                            : cipherStr == "stream" ? Cipher::STREAM
                                                    : Cipher::VIGNERE;
            IO io(filePath);
            std::fstream fileStream = io.getFileStream();
            if (fileStream.is_open()) {
                return std::make_unique<Task>(std::move(fileStream), filePath, action, cipher);
            } else {
                throw std::runtime_error("Failed to open file: " + filePath);
            }
        } else {
            throw std::runtime_error("Invalid Task Data Format");
        }
    }
};

#endif