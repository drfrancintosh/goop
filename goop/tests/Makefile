CC = gcc
CFLAGS = -Wall -g -I../includes -Wno-unsequenced -Wno-format -Wno-sequence-point -Wno-unused-value
SRC_DIR = .
OBJ_DIR = .
LIBS = -L.. -lgoop 

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

EXECUTABLE = main

all: $(EXECUTABLE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

clean:
	rm -f $(OBJ_DIR)/*.o
