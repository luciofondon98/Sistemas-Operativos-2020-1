#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include <time.h>
#include<unistd.h> 
#include<sys/types.h> 

typedef struct Topo{
    int x;
    int y;
    int iteraciones;
}topo;

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


void funcionHijo1(){
    srand(time(NULL));

    int cant_topos = (rand() % 3);

}

void funcionHijo2(int cant_topos){
    int tiempos[3];
    for (int i = 0; i < cant_topos; i++){
        tiempos[i] = (rand() % 3);
    }
    
}

void funcionHijo3(){
    
}

int main(){
	 //fd[0] = leer, fd[1] = escribir
    // int fd12[2];
    // int fd23[2];
    // int fd3p[2];
    // pipe(fd12);
    // pipe(fd23);
    // pipe(fd3p);

    int id_P, id_H1, id_H2, id_H3;
    id_P = getpid();
    id_H1 = fork();
    if (id_H1 != 0){
    	id_H2 = fork();
    	if(id_H2 != 0){
    		id_H3 = fork();
    		if (id_H3 == 0){
    			id_H3 = getpid();
    		}
    	}
      	else id_H2 = getpid();
    }
    else id_H1 = getpid();

    printf("%d %d %d %d %d\n",id_P, id_H1, id_H2, id_H3, getpid());


	// int ** tablero = crearTablero();

	return 0;
}