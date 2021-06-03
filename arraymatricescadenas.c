////////////////////////////////////////
/*
	FileName: main.c
	FileType: C source file
	Author: Sandoval Pérez, Michael Eduardo
	Created on: 02/06/2021
	Description: Creación de un arreglo dinamico que contiene matrices de cadenas de caracteres
*/
////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MatrizCadena
{
	int x;
	int y;
	char ***matriz;  // Punteor que apunta a un arreglo de punteros de cadenas de caracteres
};

typedef struct
{
	struct MatrizCadena matrizCadena;
}ListaMatrices;

typedef struct
{
	ListaMatrices *listaMatrices;
}ArrayMatricesCadenas;

ListaMatrices *insertarDatos(int, int);
void mostrarDatos(ListaMatrices*);

/*
	Función que devuelve un array de ArrayMatricesCadenas la cual recibe como parametro el tamaño del array.
	En C es imposible crear funciones que devuelvan arrays tipo [] por lo que es necesario el uso de punteros dobles **
	los cuales apuntaran a un arreglo
*/
ArrayMatricesCadenas **crearArray(int); 
/*
	Función que recibe un puntero doble (el cual apunta a un arreglo de tipo ArrayMatricesCadenas) el cual se encargará de
	imprimir los valores de cada elemente del array que contiene una matriz de cadenas de caracteres, es necesario especificar
	el tamaño del array
*/
void mostrarArray(ArrayMatricesCadenas**, int);

int main(int argc, char *argv[])
{
	int tam; 

	printf("Tamano del array: ");
	scanf("%d", &tam);

	ArrayMatricesCadenas **(*ptrCrearArray)(int) = &crearArray;

	ArrayMatricesCadenas **array = crearArray(tam);
	mostrarArray(array, tam);

	return 0;
}

ListaMatrices *insertarDatos(int _x, int _y)
{
	ListaMatrices *(lista) = (ListaMatrices*)malloc(sizeof(ListaMatrices));
	
	(*lista).matrizCadena.x = _x;
	(*lista).matrizCadena.y = _y;
	
	(*lista).matrizCadena.matriz = calloc((*lista).matrizCadena.x, sizeof(char**));
	for(int i = 0; i < (*lista).matrizCadena.x; i++)
	{
		*((*lista).matrizCadena.matriz + i) = calloc((*lista).matrizCadena.y, sizeof(char*));
		for(int j = 0; j < (*lista).matrizCadena.y; j++)
		{
			*( *( (*lista).matrizCadena.matriz + i) + j ) = malloc( sizeof(char) * ( (*lista).matrizCadena.x * (*lista).matrizCadena.y) );
			printf("Dato [%d][%d]: ", i, j);
			getchar();
			scanf("%10[0-9a-zA-Z ]", *(*((*lista).matrizCadena.matriz + i) + j));
		}
	}

	return lista;
}

void mostrarDatos(ListaMatrices* lista)
{
	for(int i = 0; i < (*lista).matrizCadena.x; i++)
	{
		printf("|");
		for(int j = 0; j < (*lista).matrizCadena.y; j++)
		{
			printf(" %s |", *( *( (*lista).matrizCadena.matriz + i) + j) );
		}	
		printf("\n");
		free(*((*lista).matrizCadena.matriz + i));
	}
	printf("\n");

	free((*lista).matrizCadena.matriz);
	free(lista);
}

ArrayMatricesCadenas **crearArray(int n)
{
	int posX, posY, i = 0;

	ArrayMatricesCadenas **(array);		// Creamos un puntero de ArrayMatricesCadenas de longitud tam
	ListaMatrices *(*ptrInsertarDatos)(int, int) = &insertarDatos;

	printf("\n\nInsertando matrices al array.\n");

	array = calloc(n, sizeof(ArrayMatricesCadenas*));
	while(i < n)			// Recupera el tamano del array
	{
		*(array + i) = malloc(sizeof(ArrayMatricesCadenas));	// Reserva memoria para cada elemento del array

		printf("\nMatriz [%d]: \n", i);
		printf("Ingresa la cantidad de filas: ");
		scanf("%d", &posX);
		printf("Ingresa la cantidad de columnas: ");
		scanf("%d", &posY);
		
		(*array[i]).listaMatrices = ptrInsertarDatos(posX, posY); // la memoria se reserva en la función

		i++;
	}

	return array;
}

void mostrarArray(ArrayMatricesCadenas** array, int n)
{
	printf("\n\nArray de matrices\n");
	int i = 0;
	while(i < n)
	{
		printf("\nMatriz [%d]\n", i);
		mostrarDatos((*array[i]).listaMatrices);
		free(*(array + i));			// Liberamos cada posición i del array
		i++;
	}
	free(array);
}
