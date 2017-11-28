EXEC = vd
CFILES = vector_dinamico.c vector_dinamico_pruebas.c testing.c main.c
HFILES = testing.h vector_dinamico.h

CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow 
VALGRINDFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2

build: $(EXEC)

run: build
	./$(EXEC) 

valgrind: build
	valgrind $(VALGRINDFLAGS) ./$(EXEC) 

clean:
	rm -f $(EXEC)

$(EXEC): $(OFILES) $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) $(OFILES) $(CFILES) -o $(EXEC)
