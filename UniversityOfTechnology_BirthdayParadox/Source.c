#define _CRT_SECURE_NO_WARNINGS
#define DNI 365 // ilo�� dni w roku
#define PROBY 30000 // ilo�� pr�b jak� ma podj�� program dla ka�dego n
#define PUSTA_WARTOSC -858993460 //warto�� jak� przyjmuje pusty indeks tablicy

#include <stdio.h>
#include <stdlib.h>

int generujLosowaLiczbe(int min, int max) //funkcja losowania liczby z podanego zakresu
{
	return (rand() % (max - min + 1)) + min; //znak % ustawia maksymalny zakres rand(), natomiast `+ min` podnosi doln� granic� od 0
}

int losujDzien(void) // funkcja korzystaj�ca z funkcji losowania liczb z okre�lonym zakresem reprezentuj�cym zakres dni roku
{
	return generujLosowaLiczbe(1, DNI); //od 1 stycznia (1. dzie� roku) do 31 grudnia (365. dzie� roku)
}

int main()
{
	int n = 1; //ilo�� os�b
	int sukces = 0; //udane pr�bki
	int daty[100]; //tablica dat urodzin
	int check = PROBY / 2; //pr�g 50% pr�b

	while (sukces <= check) //wykonuj dop�ki ilo�� udanych pr�bek nie jest wi�ksza od 50% co zachodzi dla wi�kszego prawdopodobie�stwa
	{
		sukces = 0;

		for (int i = 0; i < PROBY; i++)  // instrukcja dla pr�by
		{	
			for (int t = 0; t < n; t++) //tworzenie dat dla n os�b
				daty[t] = losujDzien();

			int kontrolna = 0; //liczba kontrolna pomagaj�ca stwierdzi� czy zaistnia�a zbie�no�� dat podczas ca�ej iteracji

			for(int e = 0; e < n; e++) // instrukcja dla ka�dej daty
			{
				pomin:
				if (daty[e] == PUSTA_WARTOSC) //sprawdzenie czy tablica jest ju� pusta i mo�na pomin�� wykonywanie dalszych instrukcji
					goto kontrola; //przejd� do nast�pnej daty (linia 56)

				for (int r = 0; r < n; r++) //przechodzenie po kolei po elementach
				{
					if (daty[r] == PUSTA_WARTOSC) //sprawdzenie czy tablica jest ju� pusta i mo�na pomin�� wykonywanie dalszych instrukcji
						goto pomin; //przejd� do nast�pnej iteracji (linia 41)

					if (daty[r] == daty[e] && &daty[e] != &daty[r]) //sprawdzenie czy dwie pozycje w tablicy maj� t� sam� warto�� i czy nie s� tymi samymi elementami tablicy (sprawdzenie adres�w w pami�ci)
					{
						//DLA SZYBSZEGO UZYSKANIA OG�LNYCH WYNIK�W SKOMENTOWA� PRINTF
						printf("kontrolna: %d  |  index: %d   |   sukces: %d   |   n: %d  : \n daty[r-1]: %d \n daty[r]: %d \n daty[r+1]: %d \n data: %d \n daty[r] address: %d \n data address: %d \n  POWTORZENIE: %d \n ------------------------------------------------------ \n //////////////////////////////////////////////////////  \n ------------------------------------------------------ \n", 
							kontrolna, r, sukces/2, n, daty[r-1], daty[r], daty[r+1], daty[e], &daty[r], &daty[e], i); // poszczeg�lny stan sk�adnik�w algorytmu kiedy zachodzi pozytywny warunek
						kontrolna++;
					}					
				}			
			} 

		kontrola:
			if (kontrolna > 0) //sprawdzenie czy istnieje chocia� jedna para
			{
				++sukces;
			}
		
		} //koniec instrukcji dla konkretnego n
		printf("Dla %d osob wynik wynosi  %d / %d prob \n", n, sukces, PROBY); // dla ka�dych sko�czonych oblicze� dla danego n wypisz ilo�� udanych pr�bek na og�
		n++;
	}
	printf("Paradoks zachodzi dla minimalnie %d osob. \n \n", n-1, sukces/2); // n-1 poniewa� p�tla while na koniec wykonywania dodaje n+1
	return 0;
}