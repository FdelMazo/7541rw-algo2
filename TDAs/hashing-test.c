#define MULT 31 //Primo
#include <stdio.h>

size_t hashing(const char* clave, size_t capacidad, size_t mult){
   size_t clave_hash = 0;
   for(size_t i = 0; clave[i] !='\0'; i++)
      clave_hash = mult * clave_hash + clave[i];
   return clave_hash % capacidad;
} 

size_t hashing2(const char* clave, size_t tam) {
	size_t hash = 0;
	size_t i = 0;
	while (clave[i] != '\0') {
		hash = (hash << 2) ^ (hash >> 14) ^ (unsigned long int) clave[i];
		i++;
	}
	return hash%tam;
}

size_t hashear(const char* clave,size_t tam){ 
	size_t hashval;
	for (hashval = 0; *clave != '\0'; clave++){
		hashval = *clave + 31 * hashval;
	}
	return hashval % tam;
}

size_t hashing3(const char* clave, size_t tam) {
	unsigned int num1 = 378551;
	unsigned int num2 = 63689;
	unsigned int clave_numerica = 0;
	for (int i = 0; *clave; clave++, i++) {
		clave_numerica = clave_numerica * num2 + (*clave);
		num2 = num2 * num1;
	}
	return (clave_numerica%tam);
}


int main(){
	char cad[] = "FEDE";
	printf("%zd", hashing(cad,53,31));
}
