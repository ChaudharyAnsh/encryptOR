#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "IO.hpp"

class readEnv {
   public:
    std::string getEnv() {
        std::string envPath = ".env";
        IO io(envPath);
        std::stringstream buffer;
        buffer << io.getFileStream().rdbuf();
        return buffer.str();
    }
};