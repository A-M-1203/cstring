CC = gcc
CFLAGS = -Wall -Wextra
SRC = test.c
TARGET = test.out

all: clean $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f *.o *.out
