CC := gcc
LD := gcc

CCFLAGS :=
CCFLAGS += -ansi -pedantic-errors
CCFLAGS += -Wall -Wextra -Iinclude
CCFLAGS += -c 

LDFLAGS := 

SRC_DIR := src
OUT_DIR := out

SRC :=
SRC += $(wildcard $(SRC_DIR)/**/**/**/*.c)
SRC += $(wildcard $(SRC_DIR)/**/**/*.c)
SRC += $(wildcard $(SRC_DIR)/**/*.c)
SRC += $(wildcard $(SRC_DIR)/*.c)

OBJ := $(SRC:.c=.o)

TARGET := $(OUT_DIR)/test

build: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CCFLAGS) $< -o $@

clean:
	rm -rf $(OBJ) $(OUT_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY:
	make clean build run

