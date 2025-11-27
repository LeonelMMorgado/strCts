CC = gcc

SRC_DIR = src
OBJ_DIR = build
INC_DIR = include
LIB_DIR = lib

FINAL = strcts

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
LIB_FILE = $(LIB_DIR)/lib$(FINAL).a

CFLAGS = -g -Wall -I$(INC_DIR) -O3

ifeq ($(OS), Windows_NT)
REMOVE = rmdir /s /q
else
REMOVE = rm -rf
endif

all: $(LIB_FILE)

$(LIB_FILE): $(OBJ_FILES) | $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR):
	mkdir $@

$(OBJ_DIR):
	mkdir $@

clean:
	$(REMOVE) $(OBJ_DIR) $(LIB_DIR)
