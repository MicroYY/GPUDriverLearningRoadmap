CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -g
CPPFLAGS := -Iinclude

BUILD_DIR := build
TEST_BIN := $(BUILD_DIR)/test_lab02

SRC := src/lab02_list.c src/job_queue.c
TEST_SRC := tests/test_lab02.c

.PHONY: all test clean

all: $(TEST_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BIN): $(SRC) $(TEST_SRC) include/lab02_list.h include/job_queue.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) $(TEST_SRC) -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)
