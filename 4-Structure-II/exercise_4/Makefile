TARGET := CleanSnake

all:
	@$(MAKE) -C LandLib -f Makefile.mk
	@$(MAKE) -C InputLib -f Makefile.mk
	@$(MAKE) -C ./ -f Makefile.mk

$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) -c -o $@ $< -I$(INCLUDE)

clean:
	rm -rf $(CURDIR)/LandLib/*.o $(CURDIR)/LandLib/*.dylib
	rm -rf $(CURDIR)/InputLib/*.o $(CURDIR)/InputLib/*.dylib
	rm -rf $(TARGET) *.o

run:
	./$(TARGET)
	
.PHONY: all clean run
