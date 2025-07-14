# Nome do executável
PRINCIPAL = chess-game

# Compilador e flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

# Ficheiros fonte
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES))

# Regras
all: $(PRINCIPAL)

$(PRINCIPAL): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR) $(PRINCIPAL)