CC=gcc
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
DEBUG_FLAG=-g
DEBUG=gdb

all: main-debug

debug: $(SRC_DIR)/main.c
	$(DEBUG) $(BIN_DIR)/main

main: $(SRC_DIR)/main.c $(INC_DIR)/user-simple.c $(INC_DIR)/timediff.c $(INC_DIR)/data_helper.c
	$(CC) -o $(BIN_DIR)/main $(SRC_DIR)/main.c $(INC_DIR)/user-simple.c $(INC_DIR)/timediff.c $(INC_DIR)/data_helper.c

main-debug: $(SRC_DIR)/main.c $(INC_DIR)/user-simple.c $(INC_DIR)/timediff.c $(INC_DIR)/data_helper.c
	$(CC) -o $(BIN_DIR)/main $(SRC_DIR)/main.c $(INC_DIR)/user-simple.c $(INC_DIR)/timediff.c $(INC_DIR)/data_helper.c $(DEBUG_FLAG)

us-example: $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c
	$(CC) -o $(BIN_DIR)/us-example $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c

us-example-debug: $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c
	$(CC) -o $(BIN_DIR)/us-example $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c $(DEBUG_FLAG)