CC := g++
SRC_FILES := $(wildcard ./*.cc)
OBJ_FILES := $(patsubst ./%.cc,./%.o,$(SRC_FILES))
LDFLAGS := -lcurses
CPPFLAGS := -Wall
TARGET := CleanSnake

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) *.o

run:
	./$(TARGET)
	
.PHONY: all clean run