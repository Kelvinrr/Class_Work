### Test MakeFile for experimenting ###
CC = gcc
TARGET = ppmrw

CPPFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

#HEADERS =
LIBS = -libc -libm

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

#HEADERS = Iincs/
#SYSHEADERS = $(subst -iframework ,-F,$(subst -isystem ,-I,$(HEADERS)))

%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) main.c -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
