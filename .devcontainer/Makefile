CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lSDL2 -lSDL2_image -lm

SRC_DIR = src
INCLUDE_DIR = include
ASSETS_DIR = assets
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
TARGET = redline

.PHONY: all clean run dirs

all: dirs $(TARGET)

dirs:
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: all
	./$(TARGET)
