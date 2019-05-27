#define _CRT_SECURE_NO_WARNINGS
#define foreach(typ, wartosc, tablica, rozmiar ) \
typ* wartosc; \
for( wartosc=tablica ; wartosc < (tablica + (rozmiar)) ; wartosc++)
#define dlugosctablicy( ary ) ( sizeof(ary)/sizeof(ary[0]) )
#define DNI 365
#define PROBY 100000
#define PUSTA_WARTOSC -858993460

#include <stdio.h>
#include <stdlib.h>

int generujLosowaLiczbe(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

int losujDzien(void)
{
	return generujLosowaLiczbe(1, DNI);
}

int main()
{
	int n = 1;
	int sukces = 0;
	int daty[100];
	int check = PROBY / 2;

	while (sukces <= check) 
	{
		sukces = 0;

		for (int i = 0; i <= PROBY; i++)  // instrukcja dla próby
		{	
			for (int i = 0; i <= n; i++) //tworzenie dat dla n osób
				daty[i] = losujDzien();

			foreach (int, data, daty, dlugosctablicy(daty)) // instrukcja dla ka¿dej daty
			{
				int kontrolna = 0;

				for (int r = 0; r < dlugosctablicy(daty); r++) //przechodzenie po kolei po elementach
				{
					if (daty[r] == PUSTA_WARTOSC)
						goto kontrola; //przejdŸ do nastêpnej daty (linia 56)

					if (daty[r] == *data)
						kontrolna++;
				}

				kontrola:
				if (kontrolna > 1)
				{				
					sukces++;
				}
			}
		
		} //koniec instrukcji dla konkretnego n
		printf("Dla %d osob wynik wynosi  %d / %d prob \n", n+1, sukces, PROBY);
		n++;
	}
	printf("Paradoks zachodzi dla minimalnie %d osob.       %d", n, sukces);
	return 0;
}