#Please construct a makefile with build and clean functionality.

PROJECT = my_test

SRC_PATH = .

CC=gcc
LIBS=-lpthread 
CSRC = $(wildcard $(addsuffix /*.c, $(SRC_PATH)))
OBJS = $(CSRC:%.c=%.o)
.PHONY = clean rebuild

rebuild: clean all

all: $(PROJECT)

$(PROJECT): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)
	
clean:
	-rm -f $(OBJS)
	-rm -f $(PROJECT)
