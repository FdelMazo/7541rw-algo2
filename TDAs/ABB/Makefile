#COMPILA TODO .C EN LA CARPETA Y LO METE EN EL EXEC
EXEC = abb
OFILES = 
CFILES = abb.c main.c pruebas_alumno.c testing.c pila.c
HFILES = abb.h testing.h pila.h

CC = gcc
CFLAGS := -g -std=c99 -Wall
CFLAGS += -Wconversion -Wno-sign-conversion -Werror -Wbad-function-cast -Wshadow
CFLAGS += -Wpointer-arith -Wunreachable-code -Wformat=2
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

#COMPILA
all: $(EXEC)

#COMPILA Y CORRE	
run: all
	./$(EXEC)

#COMPILA EN NO PEDANTIC
light: $(EXEC_NO_PEDANTIC)

#COMPILA Y CORRE Y DICE CUANTO TARDO
runtime: all
	time ./$(EXEC)

#COMPILA Y CORRE VALGRIND
valgrind: all
	valgrind $(VFLAGS) ./$(EXEC)

#COMPILA Y CORRE GDB
gdb: all
	gdb $(EXEC)

#LIMPIA LOS ARCHIVOS .O Y LOS EJECUTABLES
clean:
	rm -f $(wildcard *.o) $(EXEC)

#COMPILADOR
$(EXEC): $(CFILES) $(OFILES) $(HFILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(CFILES)
	
#COMPILADOR NO PEDANTIC	
$(EXEC_NO_PEDANTIC): $(CFILES) $(OFILES) $(HFILES)
	$(CC) -o $(EXEC) $(CFILES)
