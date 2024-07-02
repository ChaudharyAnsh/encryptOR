#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "IO.hpp"

class keyGen {
   public:
    void generate() {
        std::string envPath = ".env";
        IO io(envPath);
        std::fstream fStream = io.getFileStream();
        std::string key(256, '0'), inv(256, '0');
        for (int i = 0; i < 256; i++) {
            key[i] = i;
        }
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(key.begin(), key.end(), g);

        for (int i = 0; i < 256; i++) {
            inv[(unsigned char)key[i]] = i;
        }
        fStream << key << inv;
        std::cout << "generated key is places in .env file.\n Changing this will cause the content to be unrecoverable\n";
    }
};