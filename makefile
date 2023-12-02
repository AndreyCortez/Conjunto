CC = gcc
CFLAGS = -Wall -Wextra -Iinc

# Diretórios
SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build

# Lista de arquivos
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Nome do executável
TARGET = meu_programa

# Regras de compilação
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
    @mkdir -p $(BUILD_DIR)
    $(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) $(OBJ) -o $@

.PHONY: clean

clean:
    rm -rf $(BUILD_DIR) $(TARGET)

zip:
    zip -r projeto.zip $(SRC_DIR) $(INC_DIR) Makefile relatorio.txt
