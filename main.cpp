#include <filesystem>
#include <iostream>

#include "./src/app/processes/processManagement.hpp"
#include "./src/app/processes/task.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    std::string directory;
    std::string action;
    std::cout << "Enter the directory Path: ";
    std::getline(std::cin, directory);
    std::cout << directory << "\n";

    std::cout << "Enter the action: Encrypt/Decrypt" << std::endl;
    std::getline(std::cin, action);

    try {
        if (fs::exists(directory) && fs::is_directory(directory)) {
            processManagement pManagement;
            for (const auto &entry : fs::recursive_directory_iterator(directory)) {
                if (entry.is_regular_file()) {
                    std::string filePath = entry.path().string();
                    std::cout << filePath << std::endl;
                    IO io(filePath);
                    std::fstream fStream = io.getFileStream();
                    if (fStream.is_open()) {
                        Action act = (action == "Encrypt" ? Action::ENCRYPT : Action::DECRYPT);
                        std::unique_ptr<Task> task = std::make_unique<Task>(std::move(fStream), filePath, act);
                        pManagement.submitToQueue(std::move(task));
                    } else {
                        std::cout << "Unable to open file " << filePath << std::endl;
                    }
                }
            }
            pManagement.executeTasks();
        } else {
            std::cout << "Invalid directory path" << std::endl;
        }
    } catch (const fs::filesystem_error &err) {
        std::cout << "FileSystem Error " << err.what() << std::endl;
    }
    return 0;
}