EXEC = pila
CFILES = pila.c pruebas_alumno.c testing.c main.c
HFILES = pila.h testing.h

CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow 
CFLAGS += -Wno-unused-function #Solo para comodidad en pruebas locales
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
GDB_FLAGS = -quiet  -ex 'set pagination off' -ex 'set confirm off' -tui 

entregar: build
	$(MAKE) run; test $$? -eq 0
	$(MAKE) valgrind; test $$? -eq 0
	$(MAKE) clean
	zip $(EXEC).zip $(CFILES) $(HFILES)
	@echo "Perfecto, no falla ni pierde memoria"
	@echo "El zip esta listo para entregar"

build: $(EXEC)

run: build
	time --portability ./$(EXEC) $(LOGGING)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC) $(LOGGING)

gdb: build
	gdb $(GDB_FLAGS) ./$(EXEC)

clean:
	rm -f $(EXEC)

$(EXEC): $(OFILES) $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) $(OFILES) $(CFILES) -o $(EXEC)

batman:
	@echo "        _==/          |     |          \==_        "
	@echo "      /XX/            |\___/|            \XX\      "
	@echo "    /XXXX\            |XXXXX|            /XXXX\    "
	@echo "   |XXXXXX\_         _XXXXXXX_         _/XXXXXX|   "
	@echo "  XXXXXXXXXXXxxxxxxxXXXXXXXXXXXxxxxxxxXXXXXXXXXXX  "
	@echo " |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX| "
	@echo " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX "
	@echo " |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX| "
	@echo "  XXXXXX/^^^^^\XXXXXXXXXXXXXXXXXXXXX/^^^^^\XXXXXX  "
	@echo "   |XXX|       \XXX/^^\XXXXX/^^\XXX/       |XXX|   "
	@echo "     \XX\       \X/    \XXX/    \X/       /XX/     "
	@echo "         \              \X/             /          "
	@echo "                        \/                         "
