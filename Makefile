CC = gcc
CFLAGS = -I include -Wall -Wextra -std=c11
SRCS = $(wildcard src/*.c)
TARGET = c_invaders

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
