# Makefile for Daemon Management Program

CC = gcc
CFLAGS = -Wall -Wextra

TARGET = daemon_manager
SOURCES = daemon_manager.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJECTS)
