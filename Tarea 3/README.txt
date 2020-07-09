Nombre: Lucio Fondón 
Rol: 201773610-0

Instrucciones para utilizar la tarea:
1- Tener JDK 8 o superior instalado.
2- Para ejecutar cada problem	a, situarse dentro de su respectiva carpeta.
3- Las carpetas deben contener 2 archivos cada una, los cuales son:
	Parte 1:
		Parte1.java: Código principal que resuelve el problema sin hebras.
		makefile: Archivo que contiene las reglas de compilacion.

	Parte 2:
		Hebra.java: Código principal que resuelve el problema con implementación de hebras.
		makefile: Archivo que contiene las reglas de compilacion.

4- Una vez abierta la carpeta en la terminal, se deben realizar los siguientes pasos para compilar los archivos:

	En la terminal, escribir el siguiente comando:

	$ make

	Este comando crea el respectivo archivo .class para cada problema y los ejecuta automáticamente.
	Para borrar los archivos creados y reiniciar la compilacion, ejecutar en la terminal:

	$ make clean

Consideraciones:
-Las hebras fueron implementadas usando una clase creada llamada Hebra, la cual extiende la clase Thread de Java.
-Se utilizaron 64 hebras.
-Se puede cambiar la cantidad de hebras utilizadas si se cambia la línea 35 del archivo Hebra.java, por si se quiere experimentar
con la tarea uno mismo.
-Partí experimentando con 2 hebras, 3 hebras, 4 hebras ...  y así. Sin embargo, vi que la mejoría no era tan notable, por lo que
comencé a probar con hebras aumentando en potencias de a 2, es decir, con 2 hebras, 4 hebras, 8 hebras ... y así hasta que, con varias
pruebas de ejecución, llegué a la conclusión de que 64 hebras era la cantidad "óptima" por así decirlo para ejecutar el programa, esto
porque, fui probando también con 128 y 256 hebras, y la mejoría de tiempo era insignificante y hasta a veces se demoraba más que con 64,
por lo que se optó por dejar el programa con 64 hebras ejecutándose.

Respuestas a las preguntas: 	
1) A partir de alrededor del número N = 3000-4000 se empieza a ver la diferencia de tiempos entre los dos programas, y ya con números
más grandes, por ejemplo, de orden de magnitud de 5 (N = 100000), la diferencia es notable, demorándose el programa realizado con
hebras 3 segundos en promedio y el programa sin hebras 15 segundos en promedio.

2) Esto se debe a que, al subdividir el rango de 1 hasta N en 64 partes, cada hebra realiza su trabajo por separado al mismo tiempo,
por lo que para N alrededor de los 3000, ya la diferencia se comienza a ver en los tiempos de ejecución de cada programa.
Sin embargo, cabe destacar que, para N entre 1 y 3000, el problema sin hebras es considerablemente más rapido, esto se debe a que
el tiempo que toma el crear 64 hebras, almacenarlas en un arreglo y luego esperar a que terminen de ejecutarse, es un tiempo no
despreciable para N's muy pequeños, pero a medida que N va aumentando su tamaño, ese tiempo va haciéndose cada vez más despreciable
y comienza a ser más eficiente el programa con hebras.