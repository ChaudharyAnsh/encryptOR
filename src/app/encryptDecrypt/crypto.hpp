#ifndef CRYPTO_HPP
#define CRYPTO_HPP
#include <memory>
#include <string>

#include "../processes/task.hpp"
int executeOTPAD(std::shared_ptr<Task> task);
int executeCAESAR(std::shared_ptr<Task> task);
int executeBLOCK(std::shared_ptr<Task> task);
int executeVIGNERE(std::shared_ptr<Task> task);
#endif