ej1. `punto_t* punto = malloc(sizeof(punto));` debería ser `malloc(sizeof(punto_t));`
ej2. la api de sumar destruye los puntos, y main también después
ej3. `for(size_t i = 0; 1 < n; i++)` debería ser `for(size_t i = 0; i < n; i++)`
tokens. en vez de `malloc(sizeof(char) * strlen(s))` debería ser `malloc(strlen(s) + 1)`