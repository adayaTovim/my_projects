CXX=g++
CC=CXX

CFLAGS = -pedantic -Wall -Werror
CFLAGS += -g
CXXFLAGS = $(CFLAGS) -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS += -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc/precious_stone
SOURCES_DIR = ../../src/precious_stone
NETWORK_DIR = ../../src/network

SOURCE =  utest.cpp $(SOURCES_DIR)/udp_destination.cpp $(SOURCES_DIR)/message.cpp $(SOURCES_DIR)/file_source.cpp $(SOURCES_DIR)/file_destination.cpp $(SOURCES_DIR)/console_destination.cpp $(SOURCES_DIR)/console_source.cpp $(SOURCES_DIR)/black_box.cpp  $(SOURCES_DIR)/convert_vowel.cpp $(SOURCES_DIR)/convert_capitalize.cpp $(SOURCES_DIR)/convert_caesar.cpp $(SOURCES_DIR)/udp_source.cpp $(NETWORK_DIR)/udp.cpp
TARGET =  utest

all: $(TARGET)

$(TARGET): $(SOURCE)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) -f ./$(TARGET) *.o


.PHONY : make clean check recheck all

make:
	@echo 'Attend a maker faire'
	@${TRUE}
