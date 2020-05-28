#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include <sys/types.h> 
#include "topos.h"

typedef struct Topo{
	int x;
	int y;
	int iteraciones;
}topo;

int main(){
	//fd[0] = leer, fd[1] = escribir, 0 recibe, 1 envía
	srand(time(NULL));
	int fd12[2];
	int fd23[2];
	int fd3p[2];  
	int fdp1[2];
	int fdp2[2];
	int fdp3[2];
	
	pipe(fd12);
	pipe(fd23);
	pipe(fd3p); //creación de pipes
	pipe(fdp1);
	pipe(fdp2);
	pipe(fdp3);

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

	int ** tablero = crearTablero(), puntaje_jugador = 0;

	pid = getpid();

	if(pid == id_H1){
		close(fd12[0]);

		close(fd23[0]);
		close(fd23[1]);
		
		close(fd3p[0]);
		close(fd3p[1]);
		
		close(fdp1[1]);

		close(fdp2[0]);
		close(fdp2[1]);
		close(fdp3[0]);
		close(fdp3[1]);
		
		int mensaje = 1;
		while(1){       
			if(mensaje == 0){
				break;
			}
			
			int cant_topos = (rand() % 6); //rango de 0 a 3, no incluye al 4
			write(fd12[1],&cant_topos,sizeof(int));

			read(fdp1[0],&mensaje,sizeof(int)); //espera señal del padre para que comience de nuevo o termine
		}   
	}

	if(pid == id_H2){
		close(fd12[1]);

		close(fd3p[0]);
		close(fd3p[1]);
		
		close(fdp1[0]);
		close(fdp1[1]);
		close(fdp2[1]);
		close(fdp3[0]);
		close(fdp3[1]);

		int cant, mensaje = 1;
		while(1){
			if(mensaje == 0){
				break;
			}

			read(fd12[0],&cant,sizeof(int));
			topo * arreglo_topos = (topo*)malloc(sizeof(topo)*cant);

			//cantidad de iteraciones de cada topo
			for (int i = 0; i < cant; i++){
				arreglo_topos[i].iteraciones = (rand() % 3) + 1; //rango de 1 a 3 iteraciones
			}

			close(fd23[0]); //cierro modo lectura de hijo 2 a 3, ya que hijo 2 escribe datos a hijo 3, no lee
			write(fd23[1],arreglo_topos,sizeof(topo)*cant + 1);
			read(fdp2[0],&mensaje,sizeof(int));
		}
	}   

	if(pid == id_H3){
		close(fd3p[0]);
		
		close(fd23[1]);

		close(fd12[0]);
		close(fd12[1]);
		
		close(fdp1[0]);
		close(fdp1[1]);
		close(fdp2[0]);
		close(fdp2[1]);
		close(fdp3[1]);
		
		int mensaje = 1;
		while(1){
			if(mensaje == 0){
				break;
			}

			topo * arreglo_topos = (topo*)malloc(sizeof(topo)*5);
			read(fd23[0],arreglo_topos,sizeof(topo)*5 + 1);

			//coordenadas donde aparecerán los topos
			int x, y;
			for (int i = 0; i < 5; i++){
				if (arreglo_topos[i].iteraciones == 0) break;
				x = (rand() % 5);
				y = (rand() % 5);
				arreglo_topos[i].x = x;
				arreglo_topos[i].y = y;
			}

			write(fd3p[1],arreglo_topos,sizeof(topo)*5 + 1);
			read(fdp3[0],&mensaje,sizeof(int));
		}
	}

	if(pid == id_P){
		//primero cerrar todos los pipes que no se utilizan
		close(fd12[0]);
		close(fd12[1]);
		close(fd23[0]);
		close(fd23[1]);

		close(fd3p[1]);

		close(fdp1[0]);
		close(fdp2[0]);
		close(fdp3[0]);
		
		int opcion;

		printf("Bienvenido a Golpea el Topo. ¿Qué deseas hacer?\n\n");
		printf("1)Jugar Golpea el Topo (Modo Normal)\n");
		printf("2)Jugar Golpea el Topo (Modo Juego Rápido)\n");
		printf("3)Cerrar el programa\n");
		
		scanf("%d", &opcion);
		getchar();

		int rondas, mensaje = 1;
		if(opcion == 1){
			printf("Ingresa la cantidad de rondas que quieres jugar:\n");
			scanf("%d",&rondas); //número de iteraciones del juego
			getchar();
			printf("Vas a jugar: %d rondas.\n\n", rondas);
			printf("\n---------------------------------- MODO NORMAL ---------------------------------- \n");
			printf("Deberás ingresar las coordenadas x e y a golpear del topo, con x e y entre el 1 y el 5, inclusives.\n\n");
			while(1){
				topo * arreglo_topos = (topo*)malloc(sizeof(topo)*5);
				read(fd3p[0],arreglo_topos,sizeof(topo)*5 + 1); //tenemos todos los datos para trabajar ya
				
				//se llena el tablero con el arreglo de los topos
				if (rondas == 0){
					mensaje = 0;
					write(fdp1[1],&mensaje,sizeof(int));
					write(fdp2[1],&mensaje,sizeof(int));
					write(fdp3[1],&mensaje,sizeof(int));
					if (puntaje_jugador==1) printf("Golpeaste a %d topo en total.\n", puntaje_jugador);
					else printf("Golpeaste a %d topos en total.\n", puntaje_jugador);
					printf("Fin del juego, Adios!\n");
					break;
				}

				int cant = 0;
				for (int i = 0; i < 5; i++){
					if (arreglo_topos[i].iteraciones == 0) break;
					if (tablero[arreglo_topos[i].x][arreglo_topos[i].y] == 0){
						tablero[arreglo_topos[i].x][arreglo_topos[i].y] = arreglo_topos[i].iteraciones;
						cant++;
					}
				}

				if (cant==1) printf("Ha salido %d topo!\n",cant);
				else printf("Han salido %d topos!\n",cant);

				for (int i = 0; i < 5; i++){
					for (int j = 0; j < 5; j++){
						printf("%d ", tablero[i][j]);
					}
					printf("\n");

				}

				printf("\n");

				int x_jugador, y_jugador;
				printf("Ingrese las coordenadas x e y del topo a golpear\n");
				while(1){
					scanf("%d %d", &x_jugador,&y_jugador);
					getchar();
					if ((x_jugador > 0 && x_jugador < 6) && (y_jugador > 0 && y_jugador < 6)) break;
					else printf("Coordenadas inválidas. Intenta de nuevo\n");
				}

				printf("\n");

				if (golpearTopo(tablero,x_jugador-1,y_jugador-1)) puntaje_jugador++;
				decrementarIteraciones(tablero);
				rondas--;

				write(fdp1[1],&mensaje,sizeof(int));
				write(fdp2[1],&mensaje,sizeof(int));
				write(fdp3[1],&mensaje,sizeof(int));
			}
		}

		if(opcion == 2){
			printf("Ingresa la cantidad de rondas que quieres jugar:\n");
			scanf("%d",&rondas); //número de iteraciones del juego
			getchar();
			printf("Vas a jugar: %d rondas.\n\n", rondas);
			printf("\n---------------------------------- MODO JUEGO RÁPIDO ---------------------------------- \n");
			printf("El juego se ejecuta de forma autónoma, generando posiciones al azar donde golpear a topos.\n\n");
			while(1){
				topo * arreglo_topos = (topo*)malloc(sizeof(topo)*5);
				read(fd3p[0],arreglo_topos,sizeof(topo)*5 + 1); //tenemos todos los datos para trabajar ya
			
				if (rondas == 0){
					mensaje = 0;
					write(fdp1[1],&mensaje,sizeof(int));
					write(fdp2[1],&mensaje,sizeof(int));
					write(fdp3[1],&mensaje,sizeof(int));
					if (puntaje_jugador==1) printf("Golpeaste a %d topo en total.\n", puntaje_jugador);
					else printf("Golpeaste a %d topos en total.\n", puntaje_jugador);
					printf("Fin del juego, Adios!\n");
					break;
				}
	
				//se llena el tablero con el arreglo de los topos
				int cant = 0;
				for (int i = 0; i < 5; i++){
					if (arreglo_topos[i].iteraciones == 0) break;
					if (tablero[arreglo_topos[i].x][arreglo_topos[i].y] == 0){
						tablero[arreglo_topos[i].x][arreglo_topos[i].y] = arreglo_topos[i].iteraciones;
						cant++;
					}
				}

				if (cant==1) printf("Ha salido %d topo!\n",cant);
				else printf("Han salido %d topos!\n",cant);

				for (int i = 0; i < 5; i++){
					for (int j = 0; j < 5; j++){
						printf("%d ", tablero[i][j]);
					}
					printf("\n");

				}

				printf("\n");

				sleep(5);

				int rand_x = (rand() % 5), rand_y = (rand() % 5);
				if (golpearTopo(tablero,rand_x,rand_y)) puntaje_jugador++;
				decrementarIteraciones(tablero);
				rondas--;

				write(fdp1[1],&mensaje,sizeof(int));
				write(fdp2[1],&mensaje,sizeof(int));
				write(fdp3[1],&mensaje,sizeof(int));
			}
		}

		else{
			return 0;
		}

	}
	return 0;
}