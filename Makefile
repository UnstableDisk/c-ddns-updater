CC = gcc

CFLAGS = -Wall -Wextra -std=c17 -Iinclude

SRC := ${wildcard src/*.c} $(wildcard providers/*.c)

TARGET = ddns

all:
	$(CC) $(CFLAGS) $(SRC) -lcurl -lcjson -o $(TARGET)

clean:
	rm -f $(TARGET)
