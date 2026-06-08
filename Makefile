CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC = src/rbt.c src/rbt_rotate.c src/rbt_fixup.c src/rbt_utils.c src/main.c
OBJ = $(SRC:.c=.o)
TARGET = rbt

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)