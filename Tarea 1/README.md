Nombre: Lucio Fondón 

Rol: 201773610-0

# Instrucciones para utilizar la tarea
1) Instalar gcc
2) Abrir la terminal y entrar a la ubicación de la carpeta con los archivos en cuestión.
3) La carpeta debe contener 4 archivos, los cuales deben tener si o si los siguientes nombres:

	1) `libros.h`: Header con las funciones de `libros.c`.

	2) `libros.c`: Código principal con las funciones declaradas de `libros.h`.

	3) `main.c`: Código donde se define la funcion `main` en donde se utilizan las funciones importadas por `libros.h`.
		
	4) `makefile`: Archivo que contiene las reglas de compilacion.

4) Una vez abierta la carpeta en la terminal, se deben realizar los siguientes pasos para compilar los archivos:

	En la terminal, escribir el siguiente comando:

      ```bash
      $ make
      ```

	Este comando crea 3 archivos nuevos: `main.o`, `libros.o` y el ejecutable tarea

	Para borrar los archivos creados y reiniciar la compilacion, ejecutar en la terminal:

      ```bash
      $ make clean
      ```

# Consideraciones
- La función especificada de "navegar entre carpetas" está implícita en la opción 1 del menú, ya que da la opción de querer
consultar la opción de cualquier libro, pasando por todas las carpetas de las categorías, y luego a su vez pasando
por las carpetas de todos los autores.

- En la opción 1 y opción 3, tratar de escribir exactamente como se muestran los nombres de las categorías, y para los libros
escribirlos sin el .txt.

- Si se quieren usar sus archivos de prueba, comentar la función crearLibros() en el archivo libros.c de la línea 15 a 45,
y colocar una carpeta llamada "Libros" con todos los archivos .txt de prueba que hayan en el mismo directorio en donde
se encuentren los archivos para correr el programa.

- Si se quiere correr de nuevo debe borrarse la carpeta Libros que es generada luego de correr el programa.

- El programa viene por defecto con 50 libros a crear, si quiere editar la entrada, solo debe cambiar los parámetros del
for en la línea 18 dentro de la función crearLibros() en el archivo libros.c. (Con n > 1000 el programa mezclaba carpetas 
entre sí y se comportaba de forma extraña, así que no probaría con un n > 500).

- Por alguna razón que desconozco, si se selecciona la opción 1 del menú, y luego de volver al menú principal se selecciona alguna
opción inválida (!= de 1,2,3 o 4), entra aún así a la opción 1.

- Los autores son ordenados de mayor a menor por su promedio de notas, anteponiendo un número en sus nombres, siendo éste número
calculado de la forma (11 - promedio), cosa de que así se guarden, por ejemplo:
```bash
5. Ozuna
7. J Balvin
9. HAR
```
Por una extraña razón que desconozco, cuando ese número prefijo calculado da 10 u 11 (su promedio es 1 o 0), 
en la terminal de comandos sale:
```bash
11. Ozuna
7. J Balvin
9. HAR
```
Siendo que en el explorador de archivos sale:
```bash
7. J Balvin
9. HAR
11. Ozuna
```
Como debería ser, y no pude encontrar el error o el porqué en la terminal lo muestra así, espero lo tomes en consideración.
