CC=gcc
CFLAGS=-g -Wall -Iinclude
LIBS=-lm
TARGET= calc

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
_DEPS = functions.h stack.h conversion.h transform.h operations.h errorCheck.h
_OBJS = functions.o calc.o stack.o conversion.o transform.o operations.o errorCheck.o

DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET)
