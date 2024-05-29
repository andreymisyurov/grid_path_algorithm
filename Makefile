CC=g++

CFLAGS=-std=c++17 -Wall -Wextra

TARGET=main

all: $(TARGET) run

$(TARGET): main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(TARGET)

run:
	./main

clean:
	rm -f $(TARGET)

.PHONY: all clean
