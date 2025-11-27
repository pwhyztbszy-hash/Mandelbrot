SRC_DIR := .
OBJ_DIR := .
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

CXXFLAGS := -g -Wall -fpermissive -std=c++17
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

TARGET := mandelbrot

# Link executable
$(TARGET): $(OBJ_FILES)
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
