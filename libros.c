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

	for (int i = 0; i < 50; i++){
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
	char dirLibro[1000] = {0};
	FILE * libro;
	char dirInicial[] = "libros/";
	char dirFinal[1000] = {0};
	struct dirent *de;
	char dirCategoria[100] = {0};
	DIR *dr = opendir("libros"); 
	
	while ((de = readdir(dr)) != NULL){
		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
			continue;
		sprintf(dirLibro,"%s%s",dirInicial,de->d_name);
		printf("%s\n",dirLibro );
		libro = fopen(dirLibro,"r");
		fgets(linea,1000,libro);
		fgets(linea,1000,libro);
		fgets(linea,1000,libro);
		strtok(linea,"\n");
		sprintf(dirCategoria,"%s%s",dirInicial,linea);
		if (stat(dirCategoria, &verificar) == -1) {
			mkdir(dirCategoria, 0700);
		}
		fclose(libro);

		sprintf(dirFinal,"%s/%s",dirCategoria,de->d_name);
		rename(dirLibro, dirFinal); //movemos el libro a la carpeta de su categoría
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

// void ordenarPorMayorCategoria(){
// 	char dirAutor[1000] = {0};
// 	char dirLibro[1000] = {0};
// 	char dirInicial[] = "libros/";
// 	struct dirent *de;
// 	struct dirent *de_2;
// 	struct dirent *de_3;
// 	char carpeta_cat[1000] = {0};
// 	char linea[1000] = {0};
// 	char nombre_final[100] = {0};
// 	char dirFinal[1000] = {0};
// 	DIR *dr = opendir("libros");
// 	while ((de = readdir(dr)) != NULL){
// 		if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
// 			continue;
// 		sprintf(carpeta_cat,"%s%s",dirInicial,de->d_name); // carpeta_cat = "libros/categoria i"
// 		DIR *dr_2 = opendir(carpeta_cat);
// 		while ((de_2 = readdir(dr_2)) != NULL){
// 			if (strcmp(de_2->d_name, ".") == 0 || strcmp(de_2->d_name, "..") == 0)
// 				continue;
// 			sprintf(dirAutor,"%s/%s",carpeta_cat,de_2->d_name); //dirAutor = "libros/categoria i/autor x"  de_2->name = autor x
// 			DIR *dr_3 = opendir(dirAutor);
// 			while ((de_3 = readdir(dr_3)) != NULL){
// 				if (strcmp(de_3->d_name, ".") == 0 || strcmp(de_3->d_name, "..") == 0)
// 					continue;
// 				sprintf(dirLibro,"%s/%s",dirAutor,de_3->d_name); //dirLibro = "categoria i/autor x/libro x.txt"
// 				libro = fopen(dirLibro,"r");


// 				closedir(dr_3);
// 			}
// 		}
// 		closedir(dr_2);
// 	}
// 	closedir(dr);
// }

void ordenarPorNota(){
	int nota;
	FILE * libro;
	char dirAutor[1000] = {0};
	char dirLibro[1000] = {0};
	char dirInicial[] = "libros/";
	struct dirent *de;
	struct dirent *de_2;
	struct dirent *de_3;
	char carpeta_cat[1000] = {0};
	char linea[1000] = {0};
	char nombre_final[100] = {0};
	char dirFinal[1000] = {0};
	DIR *dr = opendir("libros");
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
		    printf("%d\n",(suma/cant_libros));
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
	char dirCategorias[] = "libros/";
	char dirLibro[1000] = {0};
	char dirAutores[1000] = {0};
	char dirFinal[1000] = {0};

	char linea[1000] = {0};
	char aux[100] = {0};

	struct dirent *de;
	DIR *dr = opendir("libros/");
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
		dr = opendir("libros/");
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

int main(){
	// crearLibros();	
	// organizarCategorias();
	// organizarAutores();
	// ordenarPorNota();
	int opcion;

	while(1){
		printf("\n-----BIENVENIDO AL ORGANIZADOR DE LIBROS XD------\n\n");
		printf("¿Qué deseas realizar?\n");
		printf("1)Consultar información de algún libro\n");
		printf("2)Recomendarte un libro al azar\n");
		printf("3)Recomendarte un libro por categoria\n");
		printf("4)Salir\n");

		scanf("%d", &opcion);
		getchar();
		if(opcion == 1){
			opcionUno();

		}	


		else if(opcion == 2){
			
		}
		
		else if(opcion == 3){
			
		}
		
		else if(opcion == 4){
			break;
		}

		else{
			printf("Haz escogido una opción incorrecta\n");
		}


	}

	return 0;
}