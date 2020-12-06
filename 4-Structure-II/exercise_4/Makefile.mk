CC := g++
SRC_FILES := $(wildcard ./*.cc)
OBJ_FILES := $(patsubst ./%.cc,./%.o,$(SRC_FILES))
LDFLAGS := -lcurses -L./InputLib/ -Wl,-rpath,$(CURDIR)/InputLib -linput -L./Landlib/ -Wl,-rpath,$(CURDIR)/LandLib -lland
CPPFLAGS := -Wall -std=c++11 -g
TARGET := CleanSnake

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) -c -o $@ $< -I$(INCLUDE)

clean:
	rm -rf $(TARGET) *.o

run:
	./$(TARGET)
	
.PHONY: all clean run

