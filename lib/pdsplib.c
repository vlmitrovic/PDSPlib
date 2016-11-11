/*
 * pdsplib.c
 *
 *  Created on: Nov 3, 2016
 *      Author: vlmitrovic
 */
#include <stdlib.h>
#include <math.h>
#include "pdsplib.h"

sinLookup_t sinLookup;

/*
 * Funkcija puni bafer "buf[]" duzine "duz" signalom belog suma
 * amplituda signala je u opsegu 0 do RAND_MAX (32768)
 */
void beliSum(int buf[], int duz) {
	int i;  // deklaracija lokalne promenljive

	if (duz>0) {  // provera duzine bafera
		for (i=0; i<duz; i++) {  // for petlja
			buf[i]=rand();  // pozivanje funkcije iz biblioteke stdlib
		}
	}
}

/*
 * Funkcija za generisanje belog suma sa ofsetom i amplitudom
 */
void beliSumOAi(int buf[], int duz, int dc, int amp) {
	int i;  // deklaracija lokalne promenljive

	if (duz>0) {  // provera duzine bafera
		for (i=0; i<duz; i++) {  // for petlja
			buf[i]=(rand()+dc)*amp;  // pozivanje funkcije iz biblioteke stdlib
		}
	}

	//TODO: Obratiti paznju na prekoracenje. Srediti funkciju da to ne moze da se dogodi.
}

void beliSumOAf(int buf[], int duz, int dc, float amp) {
	int i;  // deklaracija lokalne promenljive

	if (duz>0) {  // provera duzine bafera
		for (i=0; i<duz; i++) {  // for petlja
			buf[i]=(rand()+dc)*amp;  // pozivanje funkcije iz biblioteke stdlib
		}
	}

	//TODO: Obratiti paznju na prekoracenje. Srediti funkciju da to ne moze da se dogodi.
}

/*
 * Funkcija dodaje signalu DC offset
 */
void dodajDC(int buf[], int duz, int dc) {
	int i;

	if (duz>0) {
		for (i=0; i<duz; i++) {
			buf[i] += dc;
		}
	}

	//TODO: Obratiti paznju na prekoracenje. Srediti funkciju da to ne moze da se dogodi.
}

/*
 * Funkcija pojacava signal
 */
void pojacaj(int buf[], int duz, float amp) {
	int i;

	if (duz>0) {
		for (i=0; i<duz; i++) {
			buf[i] *= amp;
		}
	}

	//TODO: Obratiti paznju na prekoracenje. Srediti funkciju da to ne moze da se dogodi.
}

/*
 * Funkcija generise signal koji ima samo jednosmernu (DC) komponentu
 */
void dcSignal(int buf[], int duz, int dc) {
	int i;  // deklaracija lokalne promenljive

	if (duz>0 && dc<32767 && dc>-32768) {  // provera duzine bafera
		for (i=0; i<duz; i++) {  // for petlja
			buf[i]=dc;  // pozivanje funkcije iz biblioteke stdlib
		}
	}
}

/*
 * Funkcija dodaje signalu a[] signal b[]
 */
void dodajSignal(int a[], int duz, int b[]) {
    int i;  // deklaracija lokalne promenljive

    if (duz>0) {  // provera duzine bafera
        for (i=0; i<duz; i++) {  // for petlja
        	a[i]+=b[i];  // pozivanje funkcije iz biblioteke stdlib
        }
    }
}

/*
 * Funkcija mnozi svaki odbirak signala a[]
 * odgovarajucim odbirkom iz signala b[] i
 * rezultat smesta u signal a[]
 */
void pomnoziSignal(int a[], int duz, int b[]) {
    int i;  // deklaracija lokalne promenljive

    if (duz>0) {  // provera duzine bafera
        for (i=0; i<duz; i++) {  // for petlja
        	a[i]*=b[i];  // pozivanje funkcije iz biblioteke stdlib
        }
    }
}

/*
 * Primer racunanja sin(x) preko tejlorovog obrasca
 */
float tsin(float x) {  // racunanje sinusa pomocu Tejlorovog reda
	return x-((x*x*x)/6)+((x*x*x*x*x)/120)-((x*x*x*x*x*x*x)/5040);
}

/*
 * Kreiranje lookup tabele sa jednom periodom sin(x) signala
 */
void initSinLookup() {
	int x;
	float xrad;

	sinLookup.duzina=DUZ_TAB;
	if (sinLookup.duzina>0) {  // provera ispravnosti duzine niza
		for (x=0; x<sinLookup.duzina; x++) {  // generisati tabelu za sve vrednosti x od 0 do duzine tabele
			xrad=((float)x/(float)sinLookup.duzina)*_2PI;  // pretvaranje x u opseg od 0 do 2*PI
			sinLookup.tabela[x]=(int)(32767.*sin(xrad));  // Pretvaranje vrednosti u Q15 format i kastovanje u int
		}
	}
}

/*
 * Primer sin(x) funkcije koja cita iz lookup tabele, bez interpolacija
 */
float lsin(float x) {
	int i,y;
	i=(int)((x/_2PI)*sinLookup.duzina);  // racuna indeks, t=396
	y=sinLookup.tabela[i];  // uzima Q15 vrednost, t=13
	return (float)y/32767.;  // uzima vrednost iz tabele, t=319
}

/*
 * Primer sin(x) funkcije koja cita iz lookup tabele, sa interpolacijom
 */
float lsin_i(float x) {  // lookup sa interpolacijom
	float xx, yy;
	int x0, x1, y0, y1;

	xx=((x/_2PI)*sinLookup.duzina);
	x0=(int)((x/_2PI)*sinLookup.duzina);
	x1=x0+1;
	y0=sinLookup.tabela[x0];
	y1=sinLookup.tabela[x1];
	yy = (float)y0+((float)y1-(float)y0)*(xx-(float)x0);
	return yy/32767.;
}

/*
 * Kreiranje belog suma zadate amplitude u Q15 formatu
 */
void beliSumA(int buf[], int duz, int amplituda) {
	float atenuacija;

	atenuacija = (float)amplituda/16384.;
	beliSum(buf, duz);  // napravi unipolarni beli sum opseg od 0 do 32768
	dodajDC(buf, duz, -16384);
	pojacaj(buf, duz, atenuacija);
}

/*
 * Mnozenje matrica
 */
matrica_t pomnoziMatrice(matrica_t a, matrica_t b) {
	matrica_t rezultat;
	int i,j,k;

	rezultat.kolone=a.kolone;
	rezultat.redovi=b.redovi;
	for(i=0; i<a.kolone; i++) {
		for(j=0; j<b.redovi; j++) {
			rezultat.vrednosti[i][j]=0;
			for (k=0; k<a.redovi; k++) {
				rezultat.vrednosti[i][j] += a.vrednosti[i][k]*b.vrednosti[k][j];  // Pravi posao za MAC
			}
		}
	}
	return rezultat;
}


