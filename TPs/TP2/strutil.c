// Federico del Mazo - 100029
// TP1 - STRUTIL
// Corrige Gonzalo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* *****************************************************************
                         FUNCIONES AUXILIARES
 * *****************************************************************/

//Sacada de stackoverflow, retira todos los \n \0 y \t de una string
void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
        if(*s != '\t' && *s != '\n') {
            *p2++ = *s++;
        } else {
            ++s;
        }
    }
    *p2 = '\0';
} 
 
//Cuenta los separadores en una cadena 
size_t cant_sep(const char* cadena, char sep){
	size_t cantidad = 0;
	while((cadena = strchr(cadena, sep)) != NULL){
		cantidad++;
		cadena++;
	}
	return cantidad;
}
//Cuenta el total de caracteres en un arreglo de cadenas
size_t cant_chars(char** strv){
	size_t cantidad = 0;
	size_t i = 0;
	while(strv[i]){
		cantidad+=strlen(strv[i])+1;
		i++;
	}
	return cantidad;
}

//Cuenta el total de cadenas en un arreglo de cadenas
size_t cant_cads(char** strv){
	size_t cantidad = 0;
	size_t i = 0;
	while(strv[i]){
		cantidad++;
		i++;
	}
	return cantidad;
}

//Imprime un arreglo de cadenas, sirve para las pruebas
void imprimir_arreglo_cadenas(char** arreglo){
	printf("ARREGLO: ");
	for(size_t i=0; arreglo[i];i++)
		printf("\n %zd: %s", i, arreglo[i]);
	printf("\n");
}
/* *****************************************************************
                         SPLIT, JOIN y FREE_STVR
 * *****************************************************************/

char** split(const char* cadena_orig, char sep){
	char str_sep[2] = {sep, '\0'};
	size_t cant_cads = cant_sep(cadena_orig, sep) + 1;
	char **strv = malloc(sizeof(char*) * (cant_cads+2));
	char* cadena = malloc((strlen(cadena_orig) + 1) * sizeof(char));
	if(!strv || !cadena){
			free(strv);
			free(cadena);
			return NULL;
	}
	strcpy(cadena,cadena_orig);
	size_t restar = 0; //Cantidad de posiciones que avanzo mi cadena
	for(int i = 0; i<=cant_cads +1; i++)
		strv[i] = NULL;
	for(size_t i = 0; i<cant_cads; i++){
		strv[i] = NULL;
		size_t pos_sep = strcspn(cadena, str_sep);
		char* cadenita = calloc(pos_sep+1,sizeof(char));
			if(!cadenita) return NULL;
		strncpy(cadenita, cadena, pos_sep);
		strip(cadenita);
		strv[i] = cadenita;
		cadena+=pos_sep+1;
		restar +=pos_sep+1;
	}
	cadena-= restar; //Vuelvo a la posicion original para liberar la memoria
	free(cadena);
	return strv;
}

char* join(char** strv, char sep){
	if(!strv[0]){
		char* cad_vacia = malloc(sizeof(char)+1);
		if(!cad_vacia) return NULL;
		cad_vacia[0] = '\0';
		return cad_vacia;
	}
	char str_sep[2] = {sep, '\0'};
	char* cadena = calloc(cant_chars(strv),sizeof(char));
	if(!cadena) return NULL;
	char* puntero = cadena;
	strcpy(cadena,strv[0]);
	for (size_t i=1; strv[i]; i++){ 
		puntero+=strlen(puntero);
		strcat(puntero,str_sep);
		puntero++;
		strcat(puntero,strv[i]);
	}
	return cadena;
}

void free_strv(char* strv[]){
	for(size_t i = 0; strv[i]; i++)
		free(strv[i]);
	free(strv);
}

//~ int main(){
	//~ char* cad1 = "abc,def,ghi"; //abc def ghi 
	//~ char* cad2 = "abc,,def"; // abc vacio def
	//~ char* cad3 = "abc,def,"; //abc def vacio
	//~ char* cad4 = ",abc,def"; //vacio abc def
	//~ char* cad5 = ""; //vacio
	//~ char* cad6 = ","; //vacio vacio
	//~ char* cad7 = "Hola mundo"; //hola mundo
	
	//~ char** split1 = split(cad1, ',');
	//~ char** split2 = split(cad2, ',');
	//~ char** split3 = split(cad3, ',');
	//~ char** split4 = split(cad4, ',');
	//~ char** split5 = split(cad5, ',');
	//~ char** split6 = split(cad6, ',');
	//~ char** split7 = split(cad7, ' ');
	//~ char* split8[]= {NULL};
	//~ char* split9[]= {"", NULL};
	//~ char* split10[] = {"abc",NULL};
	//~ char* split11[] = {"","",NULL};
	
	//~ printf("%zd \n",cant_cads(split1));
	//~ printf("%zd \n",cant_cads(split2));
	//~ printf("%zd \n",cant_cads(split3));
	//~ printf("%zd \n",cant_cads(split4));
	//~ printf("%zd \n",cant_cads(split5));
	//~ printf("%zd \n",cant_cads(split6));
	//~ printf("%zd \n",cant_cads(split7));
	//~ printf("%zd \n",cant_cads(split8));
	//~ printf("%zd \n",cant_cads(split9));
	//~ printf("%zd \n",cant_cads(split10));
	//~ printf("%zd \n",cant_cads(split11));
	
	//~ imprimir_arreglo_cadenas(split1);
	//~ imprimir_arreglo_cadenas(split2);
	//~ imprimir_arreglo_cadenas(split3);
	//~ imprimir_arreglo_cadenas(split4);
	//~ imprimir_arreglo_cadenas(split5);
	//~ imprimir_arreglo_cadenas(split6);
	//~ imprimir_arreglo_cadenas(split7);
	//~ imprimir_arreglo_cadenas(split8);
	//~ imprimir_arreglo_cadenas(split9);
	//~ imprimir_arreglo_cadenas(split10);
	//~ imprimir_arreglo_cadenas(split11);
	
	//~ char* join1 = join(split1, ';'); //abc;def;ghi
	//~ char* join2 = join(split2, ';'); //abc;;def
	//~ char* join3 = join(split3, ';'); //abc;def;
	//~ char* join4 = join(split4, ';'); //;abc;def
	//~ char* join5 = join(split5, ';'); //vacio
	//~ char* join6 = join(split6, ';'); //;
	//~ char* join7 = join(split7, ';'); //hola;mundo
	//~ char* join8 = join(split8, ';'); //vacio
	//~ char* join9 = join(split9, ';'); //vacio
	//~ char* join10 = join(split10, ';'); //abc
	//~ char* join11 = join(split11, ';'); //";"

	//~ printf("%s \n", join1);
	//~ printf("%s \n", join2);
	//~ printf("%s \n", join3);
	//~ printf("%s \n", join4);
	//~ printf("%s \n", join5);
	//~ printf("%s \n", join6);
	//~ printf("%s \n", join7);
	//~ printf("%s \n", join8);
	//~ printf("%s \n", join9);
	//~ printf("%s \n", join10);
	//~ printf("%s \n", join11);
	
	//~ free(join1);
	//~ free(join2);
	//~ free(join3);
	//~ free(join4);
	//~ free(join5);
	//~ free(join6);
	//~ free(join7);
	//~ free(join8);
	//~ free(join9);
	//~ free(join10);
	//~ free(join11);
	
	//~ free_strv(split1);
	//~ free_strv(split2);
	//~ free_strv(split3);
	//~ free_strv(split4);
	//~ free_strv(split5);
	//~ free_strv(split6);
	//~ free_strv(split7);

	//~ return 0;
//~ }
