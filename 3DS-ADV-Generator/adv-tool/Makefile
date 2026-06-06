# ADV Tool Makefile

CC := gcc
CXX := g++
AR := ar
CFLAGS := -Wall -Wextra -O2 -I./include
LDFLAGS := -lm

SOURCES := src
INCLUDES := include
OBJ_DIR := build
BIN_DIR := bin

SOURCES_C := $(wildcard $(SOURCES)/*.c)
OBJECTS := $(patsubst $(SOURCES)/%.c,$(OBJ_DIR)/%.o,$(SOURCES_C))

TARGET := $(BIN_DIR)/adv-tool

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "✓ Build complete: $@"

$(OBJ_DIR)/%.o: $(SOURCES)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "✓ Clean complete"
