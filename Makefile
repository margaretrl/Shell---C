SRC := src
OBJ := obj
BIN := bin
EXECUTABLE := shell
MYTIMEOUT_EXECUTABLE := mytimeout

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
INCS := -Iinclude/
DIRS := $(OBJ)/ $(BIN)/
EXEC := $(BIN)/$(EXECUTABLE)
MYTIMEOUT_EXEC := $(BIN)/$(MYTIMEOUT_EXECUTABLE)

CC := gcc
CFLAGS := -g -Wall -std=c99 $(INCS)
LDFLAGS :=

all: $(EXEC) $(MYTIMEOUT_EXEC)

$(EXEC): $(filter-out $(OBJ)/mytimeout.o, $(OBJS))
	$(CC) $(CFLAGS) $^ -o $@

$(MYTIMEOUT_EXEC): $(OBJ)/mytimeout.o $(OBJ)/path_search.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	$(EXEC)

run_mytimeout: $(MYTIMEOUT_EXEC)
	$(MYTIMEOUT_EXEC)

clean:
	rm $(OBJ)/*.o $(EXEC) $(MYTIMEOUT_EXEC)

$(shell mkdir -p $(DIRS))

.PHONY: run run_mytimeout clean all
