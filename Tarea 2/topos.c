#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include <sys/types.h> 

/*Tablero de 5x5, cada topo representa 1 entero y éstos enteros representan las iteraciones de los topos
  Parte con 0 iteraciones, puesto que no hay ningún topo al crearlo*/
  
int ** crearTablero(){
	int i,j;
	int ** tablero = (int**)malloc(sizeof(int*)*5);

	for (i = 0; i < 5; i++){
		tablero[i] = (int*)malloc(sizeof(int));
			for(j = 0; j < 5; j++){
				tablero[i][j] = 0;
			}
	}
	return tablero;
}

void decrementarIteraciones(int ** tablero){
	int i,j;
	for (i = 0; i < 5; i++){
			for(j = 0; j < 5; j++){
				if (tablero[i][j] > 0){
					tablero[i][j]--;
				}
			}
	}
}

int golpearTopo(int ** tablero, int x, int y){
	if(tablero[x][y] > 0){
		printf("Golpeaste al topo en la posición (%d,%d)!\n\n",x+1, y+1);
		tablero[x][y] = 0;
		return 1;
	}
	else printf("Fallaste!\n");
	return 0;
}
