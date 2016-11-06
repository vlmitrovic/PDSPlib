/*
 * pdsplib.c
 *
 *  Created on: Nov 3, 2016
 *      Author: vlmitrovic
 */
#include <stdlib.h>

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

