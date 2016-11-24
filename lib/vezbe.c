// Biblioteke
#include "pdsplib.h"  // ukljucujem nasu pdsplib biblioteku u projekat

// Vezba 1 - https://vlmitrovic.gitbooks.io/pdsp/content/upoznavanje-sa-ccs55.html
void vezba1 () {  // pocetak programa
	// Deklaracija makroa
	#define DUZINA 512  // definisanje "konstante"

	// Deklaracija promenljivih
	int signal[DUZINA];  // deklaracija niza
	int dcsignal[DUZINA];
	matrica_t a,b,c;  // definisemo tri matrice tipa matrica_t
	
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

	// Zadatak 3 Mnozenje Matrica - prethodna vezba
	// kreiram matricu a
	a.kolone=2; a.redovi=3;
	a.vrednosti[0][0]=1; a.vrednosti[0][1]=2; a.vrednosti[0][2]=3;
	a.vrednosti[1][0]=4; a.vrednosti[1][1]=5; a.vrednosti[1][2]=6;
	// kreiram matricu b
	b.kolone=3; b.redovi=2;
	b.vrednosti[0][0]=7; b.vrednosti[0][1]=8;
	b.vrednosti[1][0]=9; b.vrednosti[1][1]=10;
	b.vrednosti[2][0]=11; b.vrednosti[2][1]=12;
	// pomnozim matrice
	if (a.redovi==b.kolone && a.kolone==b.redovi)
		c=pomnoziMatrice(a,b);

	while(1);  // beskonacna petlja
}

// Vezba 2 - https://vlmitrovic.gitbooks.io/pdsp/content/lookup-tabele.html
void vezba2() {
	int signal1[DUZ_SIG];
	int signal2[DUZ_SIG];
	int sig_sum[DUZ_SIG];
	int i;
	float x;

	// Zadatak 1
	initSinLookup();  // Inicijalizacija lookup tabele;

	for (i=0; i<DUZ_SIG; i++) {
		x = ((float)i/DUZ_SIG)*_2PI;
		signal1[i]=lsin(x)*32767;  // x=3, y=0.1482284, t=293
		signal2[i]=lsin_i(x)*32767;  // x=3, y=0.1410974, t=746
	}

	// Zadatak 2
	beliSumA(sig_sum, DUZ_SIG, (int)(32767.*(10./100.)));  // 10% maksimalne amplitude u Q15 formatu
	pojacaj(signal2, DUZ_SIG, 0.9);  // vodim racuna da signal ne udje u zasicenje pa mu smanjujem amplitudu za 10%
	dodajSignal(signal2, DUZ_SIG, sig_sum);  // sabiranje dva signala
	pojacaj(signal2, DUZ_SIG, 2./6.6);  // pripremam za izbacivanje na DAC
	dodajDC(signal2, DUZ_SIG, (1./3.3)*32767);  // dizem za 1v

	// Zadatak 3
	initQSinLookup();  // Inicijalizacija lookup tabele;
	for (i=0; i<DUZ_SIG; i++) {
		x = ((float)i/DUZ_SIG)*_2PI;
		signal1[i]=lqsin(x)*32767;
		signal2[i]=lqcos(x)*32767;
	}

	while(1);
}

// Vezba 3 - https://vlmitrovic.gitbooks.io/pdsp/content/slo%C5%BEeni-signali.html
void vezba3() {
	int signal[DUZ_SIG];

	// Zadatak 1
	// Rampa
	ramp_sig(signal,  0, 64, 1000, RASTUCA);
	ramp_sig(signal, 64, 64, 1000, RASTUCA);

	// Zadatak 2
	// Trougao
	trou_sig(signal, 0, DUZ_SIG, 1000);
	// Kvadrat, odnos signal pauza 50-50
	kvad_sig(signal, 0, DUZ_SIG, 1000, 50);
	// Trapez
	trap_sig(signal, 0, DUZ_SIG, 1000);

	// Zadatak 3
	// Rampa sacinjena od 10 sinusoida
	ramp_sin(signal, DUZ_SIG, 1000, 10, RASTUCA);
	// Trougao sacinjen od 10 sinusoida
	trou_sin(signal, DUZ_SIG, 1000, 10);
	// Kvadrat sacinjen od 10 sinusoida
	kvad_sin(signal, DUZ_SIG, 1000, 10);

	while(1);
}
