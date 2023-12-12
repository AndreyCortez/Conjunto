CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin
ZIP_FILE = projeto.zip
EXECUTABLE = $(BIN_DIR)/projeto

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
INC_FILES = $(wildcard $(INC_DIR)/*.h)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all
	./$(EXECUTABLE)

zip:
	zip -r $(ZIP_FILE) $(SRC_DIR) $(INC_DIR) makefile test_in test_out criar_casos_teste.py relatorio.txt README.md test.sh

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

test:
	bash ./test.sh 