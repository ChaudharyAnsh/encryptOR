#include <filesystem>
#include <iostream>

#include "./src/app/encryptDecrypt/crypto.hpp"
#include "./src/app/fileHanding/keyGen.cpp"
#include "./src/app/fileHanding/readEnv.cpp"
#include "./src/app/processes/task.hpp"
#include "./src/app/threading/threadPool.cpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    std::string directory;
    std::string action;
    std::string cipherStr;

    std::cout << "Enter the directory Path: ";
    std::getline(std::cin, directory);
    std::cout << directory << "\n";
    std::cout << "Enter the action: encrypt / decrypt" << std::endl;
    std::getline(std::cin, action);
    std::cout << "Enter the algorithm used: \n [ otp | caesar | block | vignere ]" << std::endl;
    std::getline(std::cin, cipherStr);

    if (action == "encrypt") {
        keyGen keyGen;
        keyGen.generate();
    }

    readEnv env;
    std::string key = env.getEnv();

    try {
        if (fs::exists(directory) && fs::is_directory(directory)) {
            threadPool pool(8);
            for (const auto &entry : fs::recursive_directory_iterator(directory)) {
                if (entry.is_regular_file()) {
                    std::string filePath = entry.path().string();
                    std::cout << filePath << std::endl;
                    IO io(filePath);
                    std::fstream fStream = io.getFileStream();
                    if (fStream.is_open()) {
                        Action act = (action == "encrypt" ? Action::ENCRYPT : Action::DECRYPT);
                        Cipher cph = (cipherStr == "otp"      ? Cipher::OTPAD
                                      : cipherStr == "block"  ? Cipher::BLOCK
                                      : cipherStr == "caesar" ? Cipher::CAESAR
                                                              : Cipher::VIGNERE);

                        std::shared_ptr<Task> task = std::make_shared<Task>(std::move(fStream), filePath, key, act, cph);
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
                        pool.executeTask(func, task);
                    } else {
                        std::cout << "Unable to open file " << filePath << std::endl;
                    }
                }
            }
        } else {
            std::cout << "Invalid directory path" << std::endl;
        }
    } catch (const fs::filesystem_error &err) {
        std::cout << "FileSystem Error " << err.what() << std::endl;
    }
    return 0;
}