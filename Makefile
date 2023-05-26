# Specify the compiler
CXX = g++

# Specify the C++ standard
CXXFLAGS = -std=c++17 -Wall -g

# Specify the SFML libraries needed for your game
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Specify the directories containing source code
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./

# Specify the name of the output executable
EXEC = $(BIN_DIR)/pokeclash

# Find all source files
SRCS = $(shell find $(SRC_DIR) -name *.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# The default target
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(SFML_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all clean

