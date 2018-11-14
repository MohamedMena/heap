CC = gcc
CFLAGS = -g -std=c99 -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2

HEADERS = heap.h testing.h
CFILES = main.c heap.c pruebas_alumno.c testing.c
TPFILES = heap.h heap.c pruebas_alumno.c

EXEC = heap
FILENAME = $(EXEC)_$(shell date +%Y%m%d).zip

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2

build: $(HEADERS) $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC)

run: build
	./$(EXEC)

all: build
	valgrind $(VFLAGS) ./$(EXEC)

zipp: 
	zip $(FILENAME) $(TPFILES)
	
clean: 
	rm -f *.o $(EXEC) $(FILENAME)
