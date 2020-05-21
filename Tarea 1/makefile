ejecucion: tarea
	./tarea

tarea: libros.o main.o
	gcc libros.o main.o -o tarea

libros.o: libros.c libros.h
	gcc -Wall -c libros.c

main.o: main.c
	gcc -c main.c -Wall

clean:
	rm tarea main.o libros.o