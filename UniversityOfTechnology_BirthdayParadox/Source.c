#define _CRT_SECURE_NO_WARNINGS
#define DNI 365 // iloœæ dni w roku
#define PROBY 30000 // iloœæ prób jak¹ ma podj¹æ program dla ka¿dego n
#define PUSTA_WARTOSC -858993460 //wartoœæ jak¹ przyjmuje pusty indeks tablicy

#include <stdio.h>
#include <stdlib.h>

int generujLosowaLiczbe(int min, int max) //funkcja losowania liczby z podanego zakresu
{
	return (rand() % (max - min + 1)) + min; //znak % ustawia maksymalny zakres rand(), natomiast `+ min` podnosi doln¹ granicê od 0
}

int losujDzien(void) // funkcja korzystaj¹ca z funkcji losowania liczb z okreœlonym zakresem reprezentuj¹cym zakres dni roku
{
	return generujLosowaLiczbe(1, DNI); //od 1 stycznia (1. dzieñ roku) do 31 grudnia (365. dzieñ roku)
}

int main()
{
	int n = 1; //iloœæ osób
	int sukces = 0; //udane próbki
	int daty[100]; //tablica dat urodzin
	int check = PROBY / 2; //próg 50% prób

	while (sukces <= check) //wykonuj dopóki iloœæ udanych próbek nie jest wiêksza od 50% co zachodzi dla wiêkszego prawdopodobieñstwa
	{
		sukces = 0;

		for (int i = 0; i < PROBY; i++)  // instrukcja dla próby
		{	
			for (int t = 0; t < n; t++) //tworzenie dat dla n osób
				daty[t] = losujDzien();

			int kontrolna = 0; //liczba kontrolna pomagaj¹ca stwierdziæ czy zaistnia³a zbie¿noœæ dat podczas ca³ej iteracji

			for(int e = 0; e < n; e++) // instrukcja dla ka¿dej daty
			{
				pomin:
				if (daty[e] == PUSTA_WARTOSC) //sprawdzenie czy tablica jest ju¿ pusta i mo¿na pomin¹æ wykonywanie dalszych instrukcji
					goto kontrola; //przejdŸ do nastêpnej daty (linia 56)

				for (int r = 0; r < n; r++) //przechodzenie po kolei po elementach
				{
					if (daty[r] == PUSTA_WARTOSC) //sprawdzenie czy tablica jest ju¿ pusta i mo¿na pomin¹æ wykonywanie dalszych instrukcji
						goto pomin; //przejdŸ do nastêpnej iteracji (linia 41)

					if (daty[r] == daty[e] && &daty[e] != &daty[r]) //sprawdzenie czy dwie pozycje w tablicy maj¹ t¹ sam¹ wartoœæ i czy nie s¹ tymi samymi elementami tablicy (sprawdzenie adresów w pamiêci)
					{
						//DLA SZYBSZEGO UZYSKANIA OGÓLNYCH WYNIKÓW SKOMENTOWAÆ PRINTF
						printf("kontrolna: %d  |  index: %d   |   sukces: %d   |   n: %d  : \n daty[r-1]: %d \n daty[r]: %d \n daty[r+1]: %d \n data: %d \n daty[r] address: %d \n data address: %d \n  POWTORZENIE: %d \n ------------------------------------------------------ \n //////////////////////////////////////////////////////  \n ------------------------------------------------------ \n", 
							kontrolna, r, sukces/2, n, daty[r-1], daty[r], daty[r+1], daty[e], &daty[r], &daty[e], i); // poszczególny stan sk³adników algorytmu kiedy zachodzi pozytywny warunek
						kontrolna++;
					}					
				}			
			} 

		kontrola:
			if (kontrolna > 0) //sprawdzenie czy istnieje chocia¿ jedna para
			{
				++sukces;
			}
		
		} //koniec instrukcji dla konkretnego n
		printf("Dla %d osob wynik wynosi  %d / %d prob \n", n, sukces, PROBY); // dla ka¿dych skoñczonych obliczeñ dla danego n wypisz iloœæ udanych próbek na ogó³
		n++;
	}
	printf("Paradoks zachodzi dla minimalnie %d osob. \n \n", n-1, sukces/2); // n-1 poniewa¿ pêtla while na koniec wykonywania dodaje n+1
	return 0;
}