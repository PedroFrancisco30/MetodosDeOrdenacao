CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -pthread
LDFLAGS  := -lm -pthread
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)
TARGET   := app
INCLUDE  := -I.
SRC      := $(wildcard *.c)

OBJECTS  := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(OBJECTS) $(LDFLAGS)

.PHONY: all build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O3
release: all

clean:
	-@rm -rvf $(OBJ_DIR)
	-@rm -rvf $(APP_DIR)/$(TARGET)

run: all
	./$(APP_DIR)/$(TARGET)