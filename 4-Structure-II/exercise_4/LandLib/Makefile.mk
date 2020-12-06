CC := clang++
SRC_DIR := ./
OBJ_DIR := ./
SRC_FILES := $(wildcard ./*.cc)
OBJ_FILES := $(patsubst ./%.cc,./%.o,$(SRC_FILES))
LDFLAGS := -lcurses
DEMOLDGLAFS := -lcurses  -L./ -Wl,-rpath,$(CURDIR) -lland
CPPFLAGS := -Wall -std=c++11 -g
TARGET := libland.dylib
DEMO := LandLibTest

$(DEMO): $(TARGET)
	$(CC) -o $@ $^ $(DEMOLDGLAFS)

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ -Wl,-install_name,$(CURDIR)/$@ -dynamiclib $(LDFLAGS) -fPIC

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) *.o *.dylib LandLibTest

run:
	./$(DEMO)
	
.PHONY: all clean run
