#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h> 
#include <unistd.h>

void crearLibros(){	
	srand(time(NULL));

	for (int i = 0; i < 15; i++){
		mkdir("libros",0700);
		char dirLibro[] = "libros/";
		char nombre_libro[20],autor[50],categoria[50], calificacion[5];
		int autor_int,fecha,nota,categoria_int;
		FILE *libro;
		sprintf(nombre_libro,"%slibro %d.txt",dirLibro,i);

		autor_int = (rand() % 5);
		fecha = (rand() % 30)+1990; // año aleatorio entre 1990 - 2020
		nota = (rand() % 10);
		categoria_int = (rand() % 3);
		sprintf(autor,"autor %d",autor_int);
		sprintf(calificacion,"%d/10",nota);
		sprintf(categoria,"categoria %d",categoria_int);

		libro = fopen(nombre_libro,"w");

		sprintf(nombre_libro,"libro %d",i);

		fprintf(libro,"%s\n",nombre_libro);
		fprintf(libro,"%s\n",autor);
		fprintf(libro,"%s\n",categoria);
		fprintf(libro,"%i\n",fecha);
		fprintf(libro,"%s\n",calificacion);
		fclose(libro);
	}	
}


void organizarCategorias(){
	struct stat verificar = {0};
	char linea[1000] = {0};
	char final[1000] = {0};
	FILE * libro;
	char dirLibro[] = "libros/";
	
	struct dirent *de;
	char categoria[100] = {0};
	DIR *dr = opendir("libros"); 
	
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		sprintf(final,"%s%s",dirLibro,de->d_name);
		printf("%s\n",final );
		libro = fopen(final,"r");
		fgets(linea,1000,libro);
		fgets(linea,1000,libro);
		fgets(linea,1000,libro);
		strtok(linea,"\n");
		sprintf(categoria,"%s%s",dirLibro,linea);
		if (stat(categoria, &verificar) == -1) {
			mkdir(categoria, 0700);
		}
		fclose(libro);

		sprintf(linea,"%s/%s",categoria,de->d_name);
		rename(final, linea); //movemos el libro a la carpeta de su categoría
	}

	closedir(dr);  

}

void organizarAutores(){
	struct stat verificar = {0};
	FILE * libro;
	char dirCategorias[] = "libros/";
	char dirLibro[1000] = {0};
	char autor[1000] = {0};
	char linea[1000] = {0};
	char final[1000] = {0};
	char carpeta_cat[1000] = {0};
	struct dirent *de;
	struct dirent *de_2;
	DIR *dr = opendir("libros/");
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		sprintf(carpeta_cat,"%s%s",dirCategorias,de->d_name); // carpeta_cat = "categorias/categoria i"
		printf("%s\n",carpeta_cat);
		DIR *dr_2 = opendir(carpeta_cat);
		while ((de_2 = readdir(dr_2)) != NULL){
			if (strcmp(de_2->d_name, ".") == 0 || strcmp(de_2->d_name, "..") == 0)
				continue;
			sprintf(dirLibro,"%s/%s",carpeta_cat,de_2->d_name); //dirLibro = "categorias/categoria i/libro x.txt"
			libro = fopen(dirLibro,"r");
			printf("%s\n",dirLibro);
			fgets(linea,100,libro);
			fgets(linea,100,libro);
			strtok(linea,"\n");
			sprintf(autor,"%s/%s",carpeta_cat,linea); //autor = "categorias/categoria i/autor x"
			if (stat(autor, &verificar) == -1){
				mkdir(autor,0700);
			}
			fclose(libro);
			sprintf(final,"%s/%s",autor,de_2->d_name); //final = "categorias/categoria i/autor x/libro x.txt

			rename(dirLibro,final);
		}
		closedir(dr_2);
	}
	closedir(dr);
}

void ordenarPorNota(){
	int nota;
	struct stat verificar = {0};
	FILE * libro;
	char dirLibro[1000] = {0};
	char dirFinal[1000] = {0};
	char dirCategorias[] = "libros/";
	struct dirent *de;
	struct dirent *de_2;
	struct dirent *de_3;
	char carpeta_cat[1000] = {0};
	char linea[1000] = {0};
	char nombre_final[100] = {0};
	char DirFinalFinal[1000] = {0};
	DIR *dr = opendir("libros");
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		sprintf(carpeta_cat,"%s%s",dirCategorias,de->d_name); // carpeta_cat = "libros/categoria i"
		DIR *dr_2 = opendir(carpeta_cat);
		while ((de_2 = readdir(dr_2)) != NULL){
			if (strcmp(de_2->d_name, ".") == 0 || strcmp(de_2->d_name, "..") == 0)
				continue;
			sprintf(dirLibro,"%s/%s",carpeta_cat,de_2->d_name); //dirLibro = "libros/categoria i/autor x"  de_2->name = autor x
			DIR *dr_3 = opendir(dirLibro);
			int cant_libros = 0;
			int suma = 0;
			int promedio;
			while ((de_3 = readdir(dr_3)) != NULL){

				if (strcmp(de_3->d_name, ".") == 0 || strcmp(de_3->d_name, "..") == 0)
					continue;
				sprintf(dirFinal,"%s/%s",dirLibro,de_3->d_name); //dirFinal = "categoria i/autor x/libro x.txt"
				libro = fopen(dirFinal,"r");
				fgets(linea,100,libro);
				fgets(linea,100,libro);
				fgets(linea,100,libro);
				fgets(linea,100,libro);
				fscanf(libro,"%d",&nota);
				suma += nota;
				cant_libros+=1;
				fclose(libro);
		    }
		    printf("%d\n",suma);
		    promedio = 11 - (suma/cant_libros);
		    sprintf(nombre_final,"%d. %s",promedio,de_2->d_name);
		    sprintf(DirFinalFinal,"%s/%s",carpeta_cat,nombre_final);
		    rename(dirLibro,DirFinalFinal);
		    closedir(dr_3);
		}
		closedir(dr_2);
	}
	closedir(dr);
}

int main(){
	crearLibros();	
	organizarCategorias();
	organizarAutores();
	ordenarPorNota();

	return 0;
}