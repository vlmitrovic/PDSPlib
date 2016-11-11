/*
 * pdsplib.h
 *
 *  Created on: Nov 3, 2016
 *      Author: vlmitrovic
 */

#ifndef PDSPLIB_H_
#define PDSPLIB_H_

#define _PI 3.14
#define _2PI 6.28
#define DUZ_TAB 64
#define MAT_MAX 10

// Struktura lookup tabele
typedef struct sinLookup_s {
	int duzina;
	int tabela[DUZ_TAB];
} sinLookup_t;

// Struktura matrice
typedef struct matrica_s {
	int kolone, redovi;
	int vrednosti[MAT_MAX][MAT_MAX];
} matrica_t;

// Deklaracija prototipova funkcija
// Funkcije koriscene u Vezbi 1
void beliSum(int buf[], int duz);
void beliSumOAi(int buf[], int duz, int dc, int amp);
void beliSumOAf(int buf[], int duz, int dc, float amp);
void dodajDC(int buf[], int duz, int dc);
void pojacaj(int buf[], int duz, float amp);
void dcSignal(int buf[], int duz, int dc);
void dodajSignal(int a[], int duz, int b[]);
void pomnoziSignal(int a[], int duz, int b[]);
matrica_t pomnoziMatrice(matrica_t a, matrica_t b);
// Funkcije koriscene u Vezbi 2
void initSinLookup();
float lsin(float x);
float lsin_i(float x);
void beliSumA(int buf[], int duz, int amplituda);

#endif /* PDSPLIB_H_ */
