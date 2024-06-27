#ifndef CRYPTO_HPP
#define CRYPTO_HPP
#include <memory>
#include <string>
#include "../processes/task.hpp"
int executeCrypto(std::unique_ptr<Task> task);

#endif