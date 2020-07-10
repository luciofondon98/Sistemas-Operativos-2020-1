Nombre: Lucio Fondón 

Rol: 201773610-0

# Instrucciones para utilizar la tarea
1) Instalar gcc
2) Abrir la terminal y entrar a la ubicación de la carpeta con los archivos en cuestión.
3) La carpeta debe contener 4 archivos, los cuales deben tener si o si los siguientes nombres:

	1) `topos.h`: Header con las funciones de `topos.c`.

	2) `topos.c`: Codigo principal con las funciones declaradas de `topos.h`.

	3) `main.c`: Codigo donde se define la funcion main en donde se utilizan las funciones importadas por
		`topos.h`

	4) `makefile`: Archivo que contiene las reglas de compilacion.

4) Una vez abierta la carpeta en la terminal, se deben realizar los siguientes pasos para compilar los archivos:

	En la terminal, escribir el siguiente comando:

      ```bash
      $ make
      ```
	Este comando crea 3 archivos nuevos: main.o, topos.o y el ejecutable tarea2
	Para borrar los archivos creados y reiniciar la compilacion, ejecutar en la terminal:

     ```bash
      $ make clean
      ```
# Consideraciones
- Al iniciar el programa habrán 3 opciones, la opción 1 es el juego en donde el usuario debe ingresar las coordenadas para golpear a cierto topo y la opción 2
es la implementación del juego rápido, en donde no deben ingresarse inputs y el juego se ejecuta de manera autónoma.

- Decidí hacer que aparezcan entre 0 y 5 topos por cada ronda, con 3 a veces se quedaba corto y aparecían muy pocos. Las demás condiciones se mantuvieron con respecto al enunciado.

- Si un topo quiere salir en una posición en donde ya hay uno levantado, éste simplemente no aparecerá y se omitirá en la cantidad de topos.

- Al iniciar el programa en cualquiera de las dos opciones se preguntará al usuario cuántas rondas del juego querrá jugar.

- Para la opción 1, al ingresar las coordenadas, deben ingresarse entre 1 y 5 inclusives (aún así, si se ingresan posiciones inválidas, éstas ya se encuentran manejadas).

- Por cada ronda se mostrará el tablero de 5x5 en la pantalla, el cual inicialmente es una matriz de enteros con ceros en todas sus posiciones, y los topos se representan 
con el número de iteraciones que aparezcan en el tablero, es decir, si `tablero[i][j] > 0`, hay un topo levantado en la posición `(i,j)`, con `tablero[i][j]` cantidad de iteraciones.
