CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -g

TARGET := ringtest

SRC := test/Ringtest.c lib/Ringbuf/Ringbuf.c
INC := -Ilib/Ringbuf

BUILD_DIR := build
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)