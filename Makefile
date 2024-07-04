CXX = g++
CXXFLAGS = -std=c++23 -g -Wall -I. -Isrc/app/encryptDecrypt -Isrc/app/fileHanding -Isrc/app/processes -Isrc/app/threading

MAIN_TARGET = encryptOR

MAIN_SRC = main.cpp \
           src/app/fileHanding/IO.cpp \
           src/app/fileHanding/readEnv.cpp \
		   src/app/threading/threadPool.cpp \
           src/app/encryptDecrypt/crypto.cpp

MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJ) $(MAIN_TARGET) 

.PHONY: clean all