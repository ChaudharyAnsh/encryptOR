#ifndef CRYPTO_HPP
#define CRYPTO_HPP
#include <memory>
#include <string>

#include "../processes/task.hpp"
int executeOTPAD(std::unique_ptr<Task> task);
int executeCAESAR(std::unique_ptr<Task> task);
int executeBLOCK(std::unique_ptr<Task> task);
int executeVIGNERE(std::unique_ptr<Task> task);
#endif