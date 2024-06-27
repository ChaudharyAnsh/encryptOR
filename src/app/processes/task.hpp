#ifndef TASK_HPP
#define TASK_HPP
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "../fileHanding/IO.hpp"

enum class Action { ENCRYPT,
                    DECRYPT };

struct Task {
    std::string filePath;
    std::fstream fStream;
    Action action;

    Task(std::fstream &&stream, std::string filePath, Action act)
        : fStream(std::move(stream)), filePath(filePath), action(act) {}

    std::string toString() {
        std::ostringstream oss;
        oss << filePath << ", "
            << (action == Action::ENCRYPT ? "Encrypt" : "Decrypt");
        return oss.str();
    }

    static std::unique_ptr<Task> fromString(const std::string &taskData) {
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;

        if (std::getline(iss, filePath, ',') && std::getline(iss, actionStr)) {
            Action action =
                actionStr == "Encrypt" ? Action::ENCRYPT : Action::DECRYPT;
            IO io(filePath);
            std::fstream fileStream = io.getFileStream();
            if (fileStream.is_open()) {
                // Task task = Task(std::move(fileStream), filePath, action);
                return std::make_unique<Task>(std::move(fileStream), filePath, action);
            } else {
                throw std::runtime_error("Failed to open file: " + filePath);
            }
        } else {
            throw std::runtime_error("Invalid Task Data Format");
        }
    }
};

#endif