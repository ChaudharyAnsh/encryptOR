CXX = g++
CXXFLAGS = -std=c++23 -g -Wall -I. -Isrc/app/encryptDecrypt -Isrc/app/fileHanding -Isrc/app/processes -Isrc/app/threading

MAIN_TARGET = encryptDecrypt
CRYPTION_TARGET = crypto

MAIN_SRC = main.cpp \
           src/app/fileHanding/IO.cpp \
           src/app/fileHanding/readEnv.cpp \
		   src/app/threading/threadPool.cpp \
           src/app/processes/processManagement.cpp \
           src/app/encryptDecrypt/crypto.cpp

CRYPTION_SRC = src/app/fileHanding/IO.cpp \
               src/app/fileHanding/readEnv.cpp \
		   	   src/app/threading/threadPool.cpp \
               src/app/encryptDecrypt/crypto.cpp \
			   src/app/encryptDecrypt/cryptoMain.cpp

MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
CRYPTION_OBJ = $(CRYPTION_SRC:.cpp=.o)

all: $(MAIN_TARGET) $(CRYPTION_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CRYPTION_TARGET): $(CRYPTION_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJ) $(CRYPTION_OBJ) $(MAIN_TARGET) $(CRYPTION_TARGET)

.PHONY: clean all