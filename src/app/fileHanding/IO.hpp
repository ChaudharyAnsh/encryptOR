#ifndef IO_HPP
#define IO_HPP
#include <fstream>
#include <string>

class IO {
   public:
    IO(const std::string &filepath);
    ~IO();
    std::fstream getFileStream();

   private:
    std::fstream fileStream;
};
#endif