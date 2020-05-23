#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include <sys/types.h> 

typedef struct Topo{
	int x;
	int y;
	int iteraciones;
}topo;

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

int main(){
	//fd[0] = leer, fd[1] = escribir, 0 recibe, 1 envía
	srand(time(NULL));
	int fd12[2];
	int fd23[2];
	int fd3p[2];  //creación de pipes
	pipe(fd12);
	pipe(fd23);
	pipe(fd3p);

	int pid, id_P, id_H1, id_H2, id_H3;
	id_P = getpid();
	id_H1 = fork();
	if (id_H1 != 0){
		id_H2 = fork();
		if(id_H2 != 0){  //creación de procesos
			id_H3 = fork();
			if (id_H3 == 0){
				id_H3 = getpid();
			}
		}
		else id_H2 = getpid();
	}
	else id_H1 = getpid();

	//printf("%d %d %d %d %d\n",id_P, id_H1, id_H2, id_H3, getppid());


	int ** tablero = crearTablero();

	pid = getpid();

	if(pid == id_H1){
		close(fd12[0]);

		close(fd23[0]);
		close(fd23[1]);
		
		close(fd3p[0]);
		close(fd3p[1]);
		
		//cantidad de topos por ronda
		int cant_topos = (rand() % 4); //rango de 0 a 3, no incluye al 4
		write(fd12[1],&cant_topos,sizeof(int));

		close(fd12[1]); //cierro modo escritura de hijo 1 a 2, ya que ya envié los datos
	}

	if(pid == id_H2){
		close(fd12[1]);

		close(fd3p[0]);
		close(fd3p[1]);
		
		int cant;
		read(fd12[0],&cant,sizeof(int));
		printf("Cantidad de topos: %d\n",cant);
		close(fd12[0]); //cierro modo lectura de hijo 1 a 2

		topo * arreglo_topos = (topo*)malloc(sizeof(topo)*cant);

		//cantidad de iteraciones de cada topo
		for (int i = 0; i < cant; i++){
			arreglo_topos[i].iteraciones = (rand() % 3) + 1; //rango de 1 a 3 iteraciones
			//printf("Iteración topo %d: %d\n",i+1,arreglo_topos[i].iteraciones); //topos e iteraciones de cada uno guardada en los arreglos
		}

		close(fd23[0]); //cierro modo lectura de hijo 2 a 3, ya que hijo 2 escribe datos a hijo 3, no lee
		write(fd23[1],arreglo_topos,sizeof(topo)*cant + 1);
		close(fd23[1]); //cierro modo escritura de hijo 2 a 3, ya que ya envié los datos
	}	

	if(pid == id_H3){
		close(fd3p[0]);
		
		close(fd23[1]);

		close(fd12[0]);
		close(fd12[1]);
		
		topo * arreglo_topos = (topo*)malloc(sizeof(topo)*3);
		read(fd23[0],arreglo_topos,sizeof(topo)*3 + 1);
		close(fd23[0]); //cierro modo lectura de hijo 2 a 3

		//coordenadas donde aparecerán los topos
		int x, y;
		for (int i = 0; i < 3; i++){
			if (arreglo_topos[i].iteraciones == 0) break;
			x = (rand() % 5);
			y = (rand() % 5);
			arreglo_topos[i].x = x;
			arreglo_topos[i].y = y;
		}

		write(fd3p[1],arreglo_topos,sizeof(topo)*3 + 1);
		close(fd3p[1]); //cierro modo escritura de hijo 3 a padre, ya que ya envié los datos
	}

	if(pid == id_P){
		close(fd23[0]);
		close(fd23[1]);

		close(fd12[0]);
		close(fd12[1]);
		
		close(fd3p[1]);

		topo * arreglo_topos = (topo*)malloc(sizeof(topo)*3);
		read(fd3p[0],arreglo_topos,sizeof(topo)*3 + 1); //tenemos todos los datos para trabajar ya
		close(fd3p[0]); //cierro modo lectura de hijo 2 a 3
		
		//se llena el tablero con el arreglo de los topos
		for (int i = 0; i < 3; i++){
			if (arreglo_topos[i].iteraciones == 0) break;
			if (tablero[arreglo_topos[i].x][arreglo_topos[i].y] == 0){
				tablero[arreglo_topos[i].x][arreglo_topos[i].y] = arreglo_topos[i].iteraciones;
			}
			printf("Iteración topo %d: %d\n",i+1,arreglo_topos[i].iteraciones);
			printf("%d %d\n",arreglo_topos[i].x,arreglo_topos[i].y); //coordenadas guardadas
		}

		for (int i = 0; i < 5; i++){
			for (int j = 0; j < 5; j++){
				printf("%d ", tablero[i][j]);
			}
			printf("\n");

		}
	}


	

	return 0;
}