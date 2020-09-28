BUILD_DIR := build

all:
	mkdir -p $(BUILD_DIR)
	gcc main.c -Wall -Werror -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR)
