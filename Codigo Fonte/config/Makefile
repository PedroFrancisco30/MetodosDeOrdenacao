CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -pthread
LDFLAGS  := -lm -pthread
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/
TARGET   := app
INCLUDE  := -Iinclude/
SRC      := $(wildcard src/*.c)

OBJECTS  := $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LDFLAGS)

.PHONY: all build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O3
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

run:
	./$(BUILD)/$(TARGET)
