#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h> 

void crearLibros(){	
	srand(time(NULL));

	for (int i = 0; i < 10; i++){
		char nombre_libro[20],autor[50],categoria[50], calificacion[5];
		int fecha,nota,categoria_int;
		FILE *libro;
		sprintf(nombre_libro,"libro %d.txt",i);
		sprintf(autor,"autor %d",i);

		fecha = (rand() % 30)+1990; // año aleatorio entre 1990 - 2020
		nota = (rand() % 10);
		categoria_int = (rand() % 10);

		sprintf(calificacion,"%d/10",nota);
		sprintf(categoria,"categoria %d",categoria_int);


		libro = fopen(nombre_libro,"w");
		
		fprintf(libro,"%s\n",nombre_libro);
		fprintf(libro,"%s\n",autor);
		fprintf(libro,"%s\n",categoria);
		fprintf(libro,"%i\n",fecha);
		fprintf(libro,"%s\n",calificacion);
		fclose(libro);
	}	
}


void crearCategorias(){
    struct stat verificar = {0};
	char linea[100] = {0};
	char final[1000] = {0};
	FILE * libro;
	char dirCategorias[] = "categorias/";
	char dirLibro[] = "libros/";
	struct dirent *de;
	char categoria[100] = {0};
    DIR *dr = opendir("libros"); 
    while ((de = readdir(dr)) != NULL){
    	if (de->d_name != NULL){
		    sprintf(final,"%s%s",dirLibro,de->d_name);
		    printf("%s\n",final );
	    	libro = fopen( final,"r");
	    	fgets(linea,1000,libro);
	    	fgets(linea,1000,libro);
	    	fgets(linea,1000,libro);
	    	sprintf(categoria,"%s%s",dirCategorias,linea);
	    	if (stat(categoria, &verificar) == -1) {
	    		mkdir(categoria, 0777);
   			}
	    	fclose(libro);

	    	sprintf(linea,"%s/%s",categoria,de->d_name);
			rename(final, linea); //movemos el libro a la carpeta de su categoría

    	}
 	}
    closedir(dr);  

}

int main(){
	crearCategorias();
	//crearLibros();
	return 0;
}