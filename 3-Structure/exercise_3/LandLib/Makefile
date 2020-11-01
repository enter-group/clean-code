CC := g++
AR := ar
SRC_FILES := $(wildcard ./*.cc)
OBJ_FILES := $(patsubst ./%.cc,./%.o,$(SRC_FILES))
LDFLAGS := -lcurses
CPPFLAGS := -Wall -std=c++11 -g
TARGET := LandLib.a
DEMO := LandLibTest

$(DEMO): $(TARGET)
	$(CC) -o $@ $^ -lcurses

$(TARGET): $(OBJ_FILES)
	$(AR) -csr $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) *.o *.a LandLibTest

run:
	./$(DEMO)
	
.PHONY: all clean run
