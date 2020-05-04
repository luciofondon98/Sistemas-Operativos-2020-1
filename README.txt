Lucio Fondon	rol: 201773610-0

Instrucciones para utilizar la tarea:
1- Instalar gcc
2- Abrir la terminal y entrar a la ubicación de la carpeta con los archivos en cuestión.
   La carpeta debe contener 5 archivos, los cuales deben tener si o si los siguientes nombres:

	libros.h: Header con las funciones de navidad.c
	libros.c: Codigo principal con las funciones declaradas de navidad.h
	main.c: Codigo donde se define la funcion main en donde se utilizan las funciones importadas por
		polinomio.h y navidad.h. El archivo debe comenzar con:

	makefile: Archivo que contiene las reglas de compilacion.
	README.txt: archivo de texto con instrucciones para correr la tarea. 

4- Una vez abierta la carpeta en la terminal, se deben realizar los siguientes pasos para compilar los archivos:

	En la terminal, escribir el siguiente comando:

	$ make

	Este comando crea 4 archivos nuevos, main.o, fun.o, genetico.o y el ejecutable genetico.
	Para borrar los archivos creados y reiniciar la compilacion, ejecutar en la terminal:

	$ make clear

Consideraciones:
-La función especificada de "navegar entre carpetas" está implícita en la opción 1 del menú, ya que da la opción de querer
consultar la opción de cualquier libro.

-Al utilizar la opción 3 del menú de recomendar un libro por categría, notar que no siempre nos entregará un libro de la categoría
que el usuario haya ingresado, esto debido a la primera condición que se pedía en la tarea ("Los autores pueden escribir libros en mas de una categora.
Por lo tanto el autor debe estar en la categoría respecto a la cual haya escrito mas libros"), por lo que, al buscar en alguna
categoría dada, por ejemplo "Terror", puede entregarme libros de categoría "Fantasía" debido a que el autor que se haya buscado
al azar pudo haber escrito libros en más de una categoría, solo que se categorizó del género "Terror" al tener más cantidad de libros en ésta.

-En la opción 1 y opción 3, tratar de escribir exactamente como se muestran los nombres de las categorías, y para los libros
escribirlos sin el .txt.

-Por alguna razón que desconozco, si se selecciona la opción 1 del menú, y luego de volver al menú principal se selecciona alguna
opción inválida (!= de 1,2,3 o 4), entra aún así a la opción 1.
