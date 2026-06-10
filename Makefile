CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = src/rbt.c src/main.c
TARGET = rbt

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)