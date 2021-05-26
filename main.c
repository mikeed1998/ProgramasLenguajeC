////////////////////////////////////////
/*
	FileName: main.c
	FileType: C source file
	Author: Sandoval Pérez, Michael Eduardo
	Created on: 25/05/2021
	Description: Creación de una matriz en lenguaje C usando cadenas (literales char) ó punteros char
*/
////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ***crearMatriz(int, int);				// Prototipo: Crear una matriz de cadenas de caracteres.
void mostrarMatriz(char***, int, int);		// Prototipo: Imprimir matriz.
void liberarMemoria(char***, int, int);		// Prototipo: Liberar la memoría. 

int main(int argc, char *argv[])
{
	int _x, _y;					// Almacenan el tamaño de las filas y columnas
	printf("Filas: ");
	scanf("%d", &_x);
	printf("Columnas: ");
	scanf("%d", &_y);

	char ***(*ptrCrearMatriz)(int, int) = &crearMatriz;		// Puntero que apunta hacia la función getMatriz
	char ***matrizCadenas = ptrCrearMatriz(_x, _y);		// Creamos e inicializamos una matriz

	mostrarMatriz(matrizCadenas, _x, _y);				// Imprime la matriz
	liberarMemoria(matrizCadenas, _x, _y);				// Liberamos la memoría de la matriz

	return 0;
}

char ***crearMatriz(int posX, int posY)	// recibe las longitudes y devuelve una matriz (la inizializa) para su uso en main
{
	char ***matriz;	// 	
	// Reserva memoria para el puntero de punteros de punteros de caracteres (matriz)			
	matriz = calloc(posX, sizeof(char**));
	for(int i = 0; i < posX; i++)	// Itera cada fila "i"
	{	//						el puntero de cadenas (literales) de caracteres
		// Reserva memoria para el puntero de punteros de caracteres (array - filas)
		*(matriz + i) = calloc(posY, sizeof(char*));	// matriz[i] = *(matriz + i)
		for(int j = 0; j < posY; j++)	// Itera cada cadena "j" dentro de cada fila "i"
		{
		/*
			Reserva una longitud de char´s para cada puntero de caracteres, lo cual nos permitirá modificar cada
			literal char (o char*) no será necesario liberar la memoria de cada char*, su función es poder modificar.
		*/
			*(*(matriz + i) + j) = malloc(sizeof(char) * (posX * posY)); // funciona también: calloc(posX * posY, sizeof(char));
			printf("Dato [%d][%d]: ", i, j);		
			scanf("%s", *(*(matriz + i) + j) );		// Inserta los datos en -> matriz[i][j] = *(*(matriz + i) + j)""" <-
		}
	}

	return matriz;	// Devuelve la matriz (o un char***)
}

void mostrarMatriz(char*** matriz, int posX, int posY) // muestra la matriz creada en main
{
	printf("\n");
	for(int i = 0; i < posX; i++)
	{
		for(int j = 0; j < posY; j++)
			printf("%s ", *(*(matriz + i) + j) );	// mostramos cada columna o cadena
		printf("\n");
	}
	printf("\n");
}

void liberarMemoria(char ***matriz, int posX, int posY)	// recibe y libera la memoria de la nuestra matriz declarada en main
{
	for(int i = 0; i < posX; i++)	// Itera cada elemento con memoria reservada
		free( *(matriz + i) );		// libera la memoria de cada char** o array
	free(matriz);					// libera la memoria del char*** o matriz
}								/*	
									No es necesario liberar cada cadena o char*, por lo cual no iteramos  
									con j ni con matriz[i][j] = *(*(matriz + i) + j)
								*/
