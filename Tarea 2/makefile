run: tarea2
	./tarea2

tarea2: topos.o main.o
	gcc topos.o main.o -o tarea2

topos.o: topos.c topos.h
	gcc -Wall -c topos.c

main.o: main.c
	gcc -c main.c -Wall

clean:
	rm tarea2 main.o topos.o