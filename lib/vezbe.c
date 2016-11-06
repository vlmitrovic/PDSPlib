// Biblioteke
#include "pdsplib.h"  // ukljucujem nasu pdsplib biblioteku u projekat

// Glavni program
void vezba1 () {  // pocetak programa
	// Deklaracija makroa
	#define DUZINA 512  // definisanje "konstante"

	// Deklaracija promenljivih
	int signal[DUZINA];  // deklaracija niza
	int dcsignal[DUZINA];
	
	// Zadatak 1.
	beliSum(signal, DUZINA);  // pozivanje funkcije za generisanje shuma
	// Zadatak 2.1.
	dodajDC(signal, DUZINA, -16384);  // dodavanje jednosmerne komponente signalu
	// Zadatak 2.2.
	pojacaj(signal, DUZINA, 2); // pojacanje signala
	// Zadatak 2.3.
	// Ove tri funkcije traju 181.393 takta kloka
	// Zadatak 2.4.
	beliSumOAf(signal, DUZINA, -16384, 2);  // generisanje suma sa ofsetom i pojacanjem
	// Zadatak 2.5.
	// Vreme trajanja ove funkcije je 161.647 taktova kloka
	// Zadatak 2.6.
	beliSumOAi(signal, DUZINA, -16384, 2);  // generisanje suma sa ofsetom i pojacanjem
	// Zadatak 2.7.
	// Vreme trajanja ove funkcije je 42.018 taktova kloka
	// Zadatak 2.8.
	beliSum(signal, DUZINA);
	dcSignal(dcsignal, DUZINA, -16384);
	// Zadatak 2.9.
	dodajSignal(signal, DUZINA, dcsignal);
	// Zadatak 2.10.
	dcSignal(dcsignal, DUZINA, 2);
	pomnoziSignal(signal, DUZINA, dcsignal);

	while(1);  // beskonacna petlja
}
