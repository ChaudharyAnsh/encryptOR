#include "IO.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <utility>

IO::IO(const std::string &filePath) {
    fileStream.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!fileStream.is_open()) {
        std::cout << "Unable to open file : " << filePath << "\n";
    }
}

std::fstream IO::getFileStream() {
    // return movale reference of fileStream;
    return std::move(fileStream);
}

IO::~IO() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}