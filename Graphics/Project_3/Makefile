### Test MakeFile for experimenting ###
CC = gcc
TARGET = raytracer

CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

INCLUDES = -Iinclude
SRC = -Isrc/

LIBS = -lm

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -c $< -o $@

$(TARGET): $(OBJECTS) src/tracer.c
	$(CC) src/tracer.c -Wall $(LIBS) $(INCLUDES) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
