#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h> 
#include <unistd.h>

typedef struct{
	int cont;
	char categoria[30];
} tipoCategoria;

void crearLibros(){	
	srand(time(NULL));

	for (int i = 0; i < 100; i++){
		mkdir("Libros",0700);
		char dirLibro[] = "Libros/";
		char nombre_libro[20],calificacion[5];
		int fecha,nota;
		FILE *libro;
		sprintf(nombre_libro,"%sLibro %d.txt",dirLibro,i);

		char autores[10][30] = {"Anuel AA","Ozuna","J Balvin","Arturo Vidal","Diego Arroyuelo","Mauricio Solar","HAR","Claudio Lobos","Juan Bahamondes","Bad Bunny"};
		char categorias[6][30] = {"Ciencia Ficción","Aventura","Drama","Terror","Fantasía","Cuento"};
		
		fecha = (rand() % 30)+1990; // año aleatorio entre 1990 - 2020
		nota = (rand() % 10);

		sprintf(calificacion,"%d/10",nota);

		libro = fopen(nombre_libro,"w");

		sprintf(nombre_libro,"Libro %d",i);

		fprintf(libro,"%s\n",nombre_libro);
		fprintf(libro,"%s\n",autores[rand() % 10]);
		fprintf(libro,"%s\n",categorias[rand() % 6]);
		fprintf(libro,"%i\n",fecha);
		fprintf(libro,"%s\n",calificacion);
		fclose(libro);
	}	
}

void ordenarCategoriasAutores(){
	struct stat verificar = {0};
	char linea[1000] = {0}, dirLibro[1000] = {0}, dirCategoria[1000], dirFinal[1000] = {0}, dirInicial[] = "Libros/", dirAutor[300] = {0}, cat_final[100];
	FILE * libro;

	struct dirent *de;
	struct dirent *de_2;

	DIR *dr = opendir("Libros"); 
	DIR *dr_2;

	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		sprintf(dirLibro,"%s%s",dirInicial,de->d_name);
		//printf("%s\n",dirLibro );
		libro = fopen(dirLibro,"r");
		fgets(linea,1000,libro);
		fgets(linea,1000,libro);
		strtok(linea,"\n");
		sprintf(dirAutor,"%s%s",dirInicial,linea);
		if (stat(dirAutor, &verificar) == -1) {
			mkdir(dirAutor, 0700);
		}
		fclose(libro);

		sprintf(dirFinal,"%s/%s",dirAutor,de->d_name);
		rename(dirLibro, dirFinal); //movemos el libro a la carpeta de su autor
	}
	closedir(dr);  

	//de aqui en adelante se busca categoria con libros mas escritos
	
	dr = opendir("Libros"); 

	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		sprintf(dirAutor,"%s%s",dirInicial,de->d_name);
		dr_2 = opendir(dirAutor);
		tipoCategoria arreglo[10];
	
		for (int j = 0; j < 10 ;j++){
			arreglo[j].cont = 0;
		}	

		while ((de_2 = readdir(dr_2)) != NULL){
			if (strcmp(de_2->d_name, ".") == 0 || strcmp(de_2->d_name, "..") == 0)
				continue;
			sprintf(dirLibro,"%s/%s",dirAutor,de_2->d_name);
			//printf("%s\n",dirLibro );
			libro = fopen(dirLibro,"r");

			fgets(linea,1000,libro);
			fgets(linea,1000,libro);
			fgets(linea,1000,libro);
			strtok(linea,"\n");
			fclose(libro);
			//printf("%s\n",linea);

			for (int k = 0; k < 10; k++){
				if (strcmp(arreglo[k].categoria,linea) == 0){
					arreglo[k].cont++;
					break;
				}
				else{
					if (strcmp(arreglo[k].categoria,"") == 0){
						strcpy(arreglo[k].categoria, linea);
						arreglo[k].cont++;
						break;
					}

				}
			}
			int cat_mas = -1 ;
			for (int k = 0; k < 10; k++){
				if (arreglo[k].cont > cat_mas){
					cat_mas = arreglo[k].cont;
					strcpy(cat_final,arreglo[k].categoria);

				}
			}
		}
		sprintf(dirCategoria,"Libros/%s",cat_final);
		if (stat(dirCategoria, &verificar) == -1) {
			mkdir(dirCategoria, 0700);
		}
		sprintf(dirFinal,"Libros/%s/%s",cat_final,de->d_name); //dirAutor = "libros/autor x" dirFinal = "libros/categoria y/autor x"
		rename(dirAutor,dirFinal);
		closedir(dr_2);
	}
	closedir(dr);	
}

void ordenarPorNota(){
	int nota;
	FILE * libro;
	char dirAutor[1000] = {0}, dirLibro[1000] = {0}, dirInicial[] = "Libros/", carpeta_cat[1000] = {0}, linea[1000] = {0}, nombre_final[300] = {0}, dirFinal[1000] = {0};

	struct dirent *de;
	struct dirent *de_2;
	struct dirent *de_3;

	DIR *dr = opendir("Libros");
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		sprintf(carpeta_cat,"%s%s",dirInicial,de->d_name); // carpeta_cat = "libros/categoria i"
		DIR *dr_2 = opendir(carpeta_cat);
		while ((de_2 = readdir(dr_2)) != NULL){
			if (strcmp(de_2->d_name, ".") == 0 || strcmp(de_2->d_name, "..") == 0)
				continue;
			sprintf(dirAutor,"%s/%s",carpeta_cat,de_2->d_name); //dirAutor = "libros/categoria i/autor x"  de_2->name = autor x
			DIR *dr_3 = opendir(dirAutor);
			int cant_libros = 0;
			int suma = 0;
			int promedio;
			while ((de_3 = readdir(dr_3)) != NULL){
				if (strcmp(de_3->d_name, ".") == 0 || strcmp(de_3->d_name, "..") == 0)
					continue;
				sprintf(dirLibro,"%s/%s",dirAutor,de_3->d_name); //dirLibro = "categoria i/autor x/libro x.txt"
				libro = fopen(dirLibro,"r");
				fgets(linea,100,libro);
				fgets(linea,100,libro);
				fgets(linea,100,libro);
				fgets(linea,100,libro);
				fscanf(libro,"%d",&nota);
				suma += nota;
				cant_libros+=1;
				fclose(libro);
			}
			promedio = 11 - (suma/cant_libros);
			sprintf(nombre_final,"%d. %s",promedio,de_2->d_name);
			sprintf(dirFinal,"%s/%s",carpeta_cat,nombre_final);
			rename(dirAutor,dirFinal);
			closedir(dr_3);
		}
		closedir(dr_2);
	}
	closedir(dr);
}

void opcionUno(){
	char dirCategorias[] = "Libros/", dirLibro[1000] = {0}, dirAutores[1000] = {0}, dirFinal[1000] = {0}, linea[1000] = {0}, aux[100] = {0};

	struct dirent *de;
	DIR *dr = opendir("Libros/");
	printf("Las categorías son las siguientes:\n");

	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		printf("%s\n", de->d_name);
	}

	closedir(dr);

	char categoria[100];
	printf("Ingrese la categoría que quiere revisar:\n");

	int flag = 1;
	while(1){
		fgets (categoria, 100, stdin);
		strtok(categoria,"\n");	
		dr = opendir("Libros/");
		while ((de = readdir(dr)) != NULL){
			if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
				continue;
			if (strcmp(de->d_name, categoria) == 0){
				flag = 0;
				break;
			}
		}
		if (flag == 0) break;
		printf("Ingresa una categoría válida.\n");
	}
	closedir(dr);

	sprintf(dirAutores,"%s%s",dirCategorias,categoria);

	dr = opendir(dirAutores);
	printf("Los autores de la %s son los siguientes: \n",categoria);
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		printf("%s\n", de->d_name);
	}

	closedir(dr);

	char autor[100];
	printf("Ingrese el autor que quiere revisar:\n");
	
	flag = 1;
	while(1){
		fgets (autor, 100, stdin);
		strtok(autor,"\n");	
		dr = opendir(dirAutores);
		while ((de = readdir(dr)) != NULL){
			if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
				continue;

			if (strstr(de->d_name, autor) != NULL){
				flag = 0;
				break;
			}
		}
		if (flag == 0) break;
		printf("Ingresa un autor válido.\n");
	}
	sprintf(dirLibro,"%s/%s",dirAutores,de->d_name);
	closedir(dr);

	dr = opendir(dirLibro);
	printf("Los libros del autor %s en la categoría %s son los siguientes: \n",autor,categoria);
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		printf("%s\n", de->d_name);
	}
	closedir(dr);

	printf("Ingresa el nombre del libro del que quieres ver su información: \n");
	
	char nombre_libro[100];
	flag = 1;
	while(1){
		fgets (nombre_libro, 100, stdin);
		strtok(nombre_libro,"\n");	
		dr = opendir(dirLibro);
		while ((de = readdir(dr)) != NULL){
			if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
				continue;
			sprintf(aux,"%s.txt",nombre_libro);
			if (strcmp(aux, de->d_name) == 0){
				flag = 0;
				break;
			}
		}
		if (flag == 0) break;
		printf("Ingresa un libro válido.\n");
	}
	sprintf(dirFinal,"%s/%s",dirLibro,de->d_name);
	closedir(dr);

	FILE * libro = fopen(dirFinal,"r");
	fgets(linea,100,libro);
	printf("\n\nTítulo del libro: %s\n",linea);
	fgets(linea,100,libro);
	printf("Autor: %s\n",linea);
	fgets(linea,100,libro);
	printf("Categoría: %s\n",linea);
	fgets(linea,100,libro);
	printf("Fecha de publicación: %s\n",linea);
	fgets(linea,100,libro);
	printf("Nota: %s\n",linea);
	fclose(libro);
}

void opcionDos(){
	srand(time(NULL));

	int i = 0;
	char categoria_rand[100];
	char autor_rand[100];
	char libro_rand[100];
	char linea[1000];
	char arreglo[100][100];
	struct dirent *de;
	DIR *dr = opendir("Libros/");
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		strcpy(arreglo[i], de->d_name);
		i++;
	}
	closedir(dr);
	sprintf(categoria_rand,"Libros/%s",arreglo[rand() % i]);

	i = 0;
	dr = opendir(categoria_rand);
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		strcpy(arreglo[i], de->d_name);
		i++;
	}
	closedir(dr);
	sprintf(autor_rand,"%s/%s",categoria_rand,arreglo[rand() % i]);

	i = 0;
	dr = opendir(autor_rand);
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		strcpy(arreglo[i], de->d_name);
		printf("%s\n", arreglo[i]);
		i++;
	}
	closedir(dr);
	sprintf(libro_rand,"%s/%s",autor_rand,arreglo[rand() % i]);

	FILE * libro = fopen(libro_rand,"r");
	fgets(linea,100,libro);
	printf("\n\nTítulo del libro: %s\n",linea);
	fgets(linea,100,libro);
	printf("Autor: %s\n",linea);
	fgets(linea,100,libro);
	printf("Categoría: %s\n",linea);
	fgets(linea,100,libro);
	printf("Fecha de publicación: %s\n",linea);
	fgets(linea,100,libro);
	printf("Nota: %s\n",linea);
	fclose(libro);
}

void opcionTres(){
	srand(time(NULL));
	
	int i = 0;
	char dirCategoria[100];
	char autor_rand[100];
	char libro_rand[100];
	char linea[1000];
	char categoria[100];
	char arreglo[100][100];
	struct dirent *de;
	DIR *dr = opendir("Libros/");
	printf("Las categorías son las siguientes:\n");
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		printf("%s\n", de->d_name);
	}

	closedir(dr);

	int flag = 1;
	while(1){
		fgets (categoria, 100, stdin);
		strtok(categoria,"\n");	
		dr = opendir("Libros/");
		while ((de = readdir(dr)) != NULL){
			if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
				continue;
			if (strcmp(de->d_name, categoria) == 0){
				flag = 0;
				break;
			}
		}
		if (flag == 0) break;
		printf("Ingresa una categoría válida.\n");
	}
	closedir(dr);

	sprintf(dirCategoria,"Libros/%s",categoria);


	i = 0;
	dr = opendir(dirCategoria);
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		strcpy(arreglo[i], de->d_name);
		i++;
	}
	closedir(dr);
	sprintf(autor_rand,"%s/%s",dirCategoria,arreglo[rand() % i]);

	i = 0;
	dr = opendir(autor_rand);
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		strcpy(arreglo[i], de->d_name);
		i++;
	}
	closedir(dr);
	sprintf(libro_rand,"%s/%s",autor_rand,arreglo[rand() % i]);

	FILE * libro = fopen(libro_rand,"r");
	fgets(linea,100,libro);
	printf("\n\nTítulo del libro: %s\n",linea);
	fgets(linea,100,libro);
	printf("Autor: %s\n",linea);
	fgets(linea,100,libro);
	printf("Categoría: %s\n",linea);
	fgets(linea,100,libro);
	printf("Fecha de publicación: %s\n",linea);
	fgets(linea,100,libro);
	printf("Nota: %s\n",linea);
	fclose(libro);
}
