CC=gcc
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
DEBUG_FLAG=-g
DEBUG=gdb
PTHREADS_FLAG=-l pthread

all: clean main us-example urr-example

debug: $(SRC_DIR)/main.c
	$(DEBUG) $(BIN_DIR)/main

main: $(SRC_DIR)/main.c $(INC_DIR)/user-simple.c $(INC_DIR)/kernel-simple.c $(INC_DIR)/timediff.c $(INC_DIR)/data_helper.c $(INC_DIR)/user-roundrobin.c
	$(CC) -o $(BIN_DIR)/main $(SRC_DIR)/main.c $(INC_DIR)/user-simple.c $(INC_DIR)/kernel-simple.c $(INC_DIR)/timediff.c $(INC_DIR)/data_helper.c $(PTHREADS_FLAG) $(INC_DIR)/user-roundrobin.c

main-debug: $(SRC_DIR)/main.c $(INC_DIR)/user-simple.c $(INC_DIR)/kernel-simple.c $(INC_DIR)/timediff.c $(INC_DIR)/data_helper.c $(INC_DIR)/user-roundrobin.c
	$(CC) -o $(BIN_DIR)/main $(SRC_DIR)/main.c $(INC_DIR)/user-simple.c $(INC_DIR)/kernel-simple.c $(INC_DIR)/timediff.c $(INC_DIR)/data_helper.c $(DEBUG_FLAG) $(PTHREADS_FLAG) $(INC_DIR)/user-roundrobin.c

us-example: $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c
	$(CC) -o $(BIN_DIR)/us-example $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c

us-example-debug: $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c
	$(CC) -o $(BIN_DIR)/us-example $(SRC_DIR)/examples/us-example.c $(INC_DIR)/user-simple.c $(DEBUG_FLAG)

urr-example: $(SRC_DIR)/examples/urr-example.c $(INC_DIR)/user-roundrobin.c
	$(CC) -o $(BIN_DIR)/urr-example $(SRC_DIR)/examples/urr-example.c $(INC_DIR)/user-roundrobin.c

urr-example-debug: $(SRC_DIR)/examples/urr-example.c $(INC_DIR)/user-roundrobin.c
	$(CC) -o $(BIN_DIR)/urr-example $(SRC_DIR)/examples/urr-example.c $(INC_DIR)/user-roundrobin.c $(DEBUG_FLAG)

clean:
	rm -rf $(BIN_DIR)/*