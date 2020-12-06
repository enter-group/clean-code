CC := clang++
SRC_DIR := ./
OBJ_DIR := ./
SRC_FILES := $(wildcard ./*.mm)
OBJ_FILES := $(patsubst ./%.mm,./%.o,$(SRC_FILES))
CPPFLAGS := -Wall -g -std=c++11
LIB := -lois 
FRAMEWORKS := -framework Foundation -framework IOKit -framework AppKit -framework Cocoa -framework Carbon
TARGET := libinput.dylib

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ -Wl,-install_name,$(CURDIR)/$@  -dynamiclib  $(FRAMEWORKS) $(LIB) $(LDFLAGS) -fPIC

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.mm
	$(CC) $(CPPFLAGS) -ObjC++ -c -o $@ $<

clean:
	rm -rf $(TARGET) *.o *.dylib
	
.PHONY: all clean run
