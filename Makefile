CC = gcc
CFLAGS = -Wall -Wextra -g
OBJECTS = $(wildcard *.c)
TARGET = uniqueid

all:
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)
clean:
	rm -f $(TARGET)
