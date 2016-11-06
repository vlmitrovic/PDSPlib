/*
 * pdsplib.h
 *
 *  Created on: Nov 3, 2016
 *      Author: vlmitrovic
 */

#ifndef PDSPLIB_H_
#define PDSPLIB_H_

// Deklaracija prototipova funkcija
void beliSum(int buf[], int duz);
void beliSumOAi(int buf[], int duz, int dc, int amp);
void beliSumOAf(int buf[], int duz, int dc, float amp);
void dodajDC(int buf[], int duz, int dc);
void pojacaj(int buf[], int duz, float amp);
void dcSignal(int buf[], int duz, int dc);
void dodajSignal(int a[], int duz, int b[]);
void pomnoziSignal(int a[], int duz, int b[]);

#endif /* PDSPLIB_H_ */
