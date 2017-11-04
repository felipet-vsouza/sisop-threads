CC=gcc
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: us-example

us-example: $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c
	$(CC) -o $(BIN_DIR)/us-example $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c