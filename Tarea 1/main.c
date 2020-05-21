#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "libros.h"


int main(){
	crearLibros();	
	ordenarCategoriasAutores();
	ordenarPorNota();
	int opcion;

	while(1){
		printf("\n-----BIENVENIDO AL ORGANIZADOR DE LIBROS XD------\n\n");
		printf("¿Qué deseas realizar?\n");
		printf("1)Consultar información de algún libro\n");
		printf("2)Recomendarte un libro al azar\n");
		printf("3)Recomendarte un libro por categoria\n");
		printf("4)Salir\n");

		scanf("%d", &opcion);
		getchar();

		if(opcion == 1){
			opcionUno();
		}	
		else if(opcion == 2){
			opcionDos();
		}
		
		else if(opcion == 3){
			opcionTres();
		}
		
		else if(opcion == 4){
			break;
		}

		else{
			printf("Haz escogido una opción incorrecta\n");
		}
	}
	return 0;
}