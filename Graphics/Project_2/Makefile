### Test MakeFile for experimenting ###
CC = gcc
TARGET = tracer

CPPFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

LIBS = -lm
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) tracer.c
	$(CC) tracer.c -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
