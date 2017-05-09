/*
* @file		Examinador.c
*
* @brief	Aplica y califica examenes a partir de un archivo CSV
*
* @author Lucas Comamala, Angeles Contreras, Brenda Themsel 
* @date 	27/04/2017
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "csvparser.h"

void shuffle (int arr[], int n);
void swap (int *a, int *b);

void examinador () {

  /* Variables para medir el tiempo */ 
 	double segundos = 0;
	double milis;
	struct timeval final, inicio;
	gettimeofday(&inicio, NULL);
	
	/***************/
	/** Variables **/
	/***************/
	
	int i, count=0, index, n;
	char answer;
	char stream[40];
	long id;
	
	/* Nombre del examen */
	printf("Ingrese el nombre del examen (sin la extension):\n");
	scanf(" %[^\n]", stream);
	strcat(stream, ".csv");
	printf("\n");
	
	/* Nombre del examen */
	printf("ID del alumno que va a tomar el examen:\n");
	scanf("%li", &id);
	printf("\n");
	
	/* Checa la cantidad de preguntas que hay en el examen */
	CsvParser *csvparserT = CsvParser_new(stream, ",", 0);
	CsvRow *rowT;
	rowT = CsvParser_getRow(csvparserT);
	n = CsvParser_getNumFields(rowT);
	CsvParser_destroy_row(rowT);
	CsvParser_destroy(csvparserT);
	
	/* Arrays para los reactivos y las respuestas */
	char reactivos[n][100];
	char resA[n][100];
	char resB[n][100];
	char resC[n][100];
	char resD[n][100];
	
	char respuestasTemp[4][100];
	
	/* Array para los puntosstream de cada reactivo */
	int puntos[n];
	
	/* Index arrays */
	int reactivosInd[n];
	for (i=0; i<n; i++)
		reactivosInd[i] = i;
	int respuestasInd[] = {0, 1, 2, 3};
	
	//int nn = sizeof(reactivosInd)/ sizeof(reactivosInd[0]);
	
	/********************/
	/** Inicializacion **/
	/********************/
	
	/* CsvParser
	*  Author: James Ramm
	*  Link: https://github.com/JamesRamm/csv_parser
	*/
	CsvParser *csvparser = CsvParser_new(stream, ",", 0);
	CsvRow *row;

	while ((row = CsvParser_getRow(csvparser)) ) {
		const char **rowFields = CsvParser_getFields(row);
		for (i = 0 ; i < CsvParser_getNumFields(row) ; i++) {
			switch (count) {
				case 0:
					strcpy(reactivos[i], rowFields[i]);
					break;
				case 1:
					strcpy(resA[i], rowFields[i]);
					break;
				case 2:
					strcpy(resB[i], rowFields[i]);
					break;
				case 3:
					strcpy(resC[i], rowFields[i]);
					break;
				case 4:
					strcpy(resD[i], rowFields[i]);
					break;
				case 5:
					puntos[i] = atoi(rowFields[i]);
					break;
			}
		}
		count++;
		CsvParser_destroy_row(row);
	}
	CsvParser_destroy(csvparser);

	/***********************/
	/** Aplicar el examen **/
	/***********************/
	
	shuffle(reactivosInd, n);
 	
 	/* Iteramos n veces (cuantas preguntas) */
	for (i=0; i<n; i++) {
 	
		/* Imprimimos la pregunta */
		printf("%d.- %s\n", i+1, reactivos[reactivosInd[i]]);
		
		/* Creamos un array temporal con las respuestas de una solo pregunta y utilizamos shuffle */
		strcpy(respuestasTemp[0], resA[reactivosInd[i]]);
		strcpy(respuestasTemp[1], resB[reactivosInd[i]]);
		strcpy(respuestasTemp[2], resC[reactivosInd[i]]);
		strcpy(respuestasTemp[3], resD[reactivosInd[i]]);
		
		shuffle(respuestasInd, 4);	 	
		
		/* Imprimimos las respuestas */
		printf("  A - %s\n", respuestasTemp[respuestasInd[0]]);
		printf("  B - %s\n", respuestasTemp[respuestasInd[1]]);
		printf("  C - %s\n", respuestasTemp[respuestasInd[2]]);
		printf("  D - %s\n", respuestasTemp[respuestasInd[3]]);

	
		/* Capturamos y validamos la respuesta del usuario */
		while (1) {
		  
			scanf(" %c", &answer);
			answer = toupper(answer);
		
			if ( answer=='A' || answer=='B' || answer=='C' || answer=='D' ) break;
		}
	
		/* Checamos si la respuesta dada es la Correctoa */
		if ( answer == 'A')
			if ( strcmp(respuestasTemp[respuestasInd[0]], resA[reactivosInd[i]]) == 0 )
				printf("Correcto\n");
			else
				printf("Incorrecto\n");
		
		else if ( answer == 'B')
			if ( strcmp(respuestasTemp[respuestasInd[1]], resA[reactivosInd[i]]) == 0 )
				printf("Correcto\n");
			else
				printf("Incorrecto\n");
		
		else if ( answer == 'C')
			if ( strcmp(respuestasTemp[respuestasInd[2]], resA[reactivosInd[i]]) == 0 )
				printf("Correcto\n");
			else
				printf("Incorrecto\n");
		
		else if ( answer == 'D')
			if ( strcmp(respuestasTemp[respuestasInd[3]], resA[reactivosInd[i]]) == 0 )
				printf("Correcto\n");
			else
				printf("Incorrecto\n");
		
		printf("\n");
	 	
} //end_for
	
	
	/**************************************/
	/** Display de Resultados del Examen **/
	/**************************************/
	
	//Imprime resultados de tiempo :
	gettimeofday(&final, NULL);//fin del clock
	segundos = (double)(final.tv_usec - inicio.tv_usec) / 1000000 + (double)(final.tv_sec - inicio.tv_sec);//obtenemos cuanto se tardi 
	printf("Tiempo en el que se realizo el examen: %3.2f segundos\n", segundos);//ponemos cuanto tiempo se tardo el alumno en realizar el examn	
	
}//fin del main 

/* 
*	Funcion que cambia la posicion de dos ints en un arreglo 
*	Autor: Lucas Comamala
*/
void swap (int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
*	Funcion que  altera el orden de un arreglo de intsutilizandop la funcion swap().
*	Lo utilizamos para elegir preguntas en desorden
*	Autor: Lucas Comamala
*/
void shuffle (int arr[], int n) {

	srand(time(NULL));
	int i;
	
	for (i = n-1; i > 0; i--) {
		int j = rand() % (i+1);
		swap(&arr[i], &arr[j]);
	}
}
