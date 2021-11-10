CC ?= gcc
CFLAG ?= -Wall
TARGET = bb.out
SOURCES = board.c main.c resistor.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAG) $(SOURCES) -o $(TARGET)