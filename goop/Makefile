CC = gcc
CFLAGS = -Wall -g -I./includes -Wno-unsequenced -Wno-format -Wno-sequence-point -Wno-unused-value
ARFLAGS = -rcs
SRC_DIR = ./src
OBJ_DIR = ./objs
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

EXECUTABLE = main
LIBRARY = libgoop.a

all: $(LIBRARY)

mac_build: $(LIBRARY)
	cp $(LIBRARY) ../mac_libs
	cp ./includes/*.h ../includes

pico_build: $(LIBRARY)
	cp $(LIBRARY) ../mac_libs
	cp ./includes/*.h ../includes

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBRARY): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -r *.a
