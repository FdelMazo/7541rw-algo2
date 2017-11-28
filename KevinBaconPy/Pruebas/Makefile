LIB = seis_grados.py

SALIDA = "Pruebas para Python3 no ejecutadas."
SALIDA += "\nEl trabajo esta en otro lenguaje de programacion o no contiene el archivo '$(LIB)'"

test:
ifeq ($(findstring $(LIB), $(wildcard *.py)), $(LIB))
	python3 tests.py
else
	@echo  $(SALIDA)
endif
