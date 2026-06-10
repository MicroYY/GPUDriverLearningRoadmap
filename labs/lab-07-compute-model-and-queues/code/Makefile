CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -g
CPPFLAGS := -Iinclude

BUILD_DIR := build
TEST_BIN := $(BUILD_DIR)/test_queue_ops

SRC := src/queue_ops.c
TEST_SRC := tests/test_queue_ops.c

.PHONY: all test clean

all: $(TEST_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BIN): $(SRC) $(TEST_SRC) include/queue_ops.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) $(TEST_SRC) -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)
