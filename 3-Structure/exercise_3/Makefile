CC := g++
SRC_FILES := $(wildcard ./*.cc)
OBJ_FILES := $(patsubst ./%.cc,./%.o,$(SRC_FILES))
LDFLAGS := -lcurses
CPPFLAGS := -Wall -std=c++11 -g
TARGET := CleanSnake
LIB := LandLib/Landlib.a
INCLUDE := LandLib

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LIB) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) -c -o $@ $< -I$(INCLUDE)

clean:
	rm -rf $(TARGET) *.o

run:
	./$(TARGET)
	
.PHONY: all clean run
