#define _CRT_SECURE_NO_WARNINGS
#define foreach(idxtype, idxpvar, col, colsiz ) idxtype* idxpvar; for( idxpvar=col ; idxpvar < (col + (colsiz)) ; idxpvar++)
#define arraylen( ary ) ( sizeof(ary)/sizeof(ary[0]) )
#define DNI 365
#define PROBY 30000

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int generujLosowaLiczbe(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

int losujDzien(void)
{
	return generujLosowaLiczbe(1, DNI);
}

int* przydzielDaty(int size)
{
	int *arr = malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
		arr[i] = losujDzien();
	return *arr;
}

int main()
{
	int n = 1;
	int sukces = 0;
	int daty[100];
	int check = PROBY / 2;

	while (sukces <= check) 
	{
		for (int i = 0; i < PROBY; i++) 
		{	
			for (int i = 0; i < n; i++)
				daty[i] = losujDzien();

			int kontrolna = 0;

			foreach (int, date, daty, arraylen(daty)) 
			{
				int size = arraylen(daty);
				for (int r = 0; r < size; r++)
				{
					if (daty[r] < 1 && daty[r] != -858993460 || daty[r] > 365 && daty[r] != -858993460)
					{
						printf("chuj kurwa");
					}
					if (daty[r] == -858993460 || *date == -858993460)
						goto kontrola;

					if (daty[r] == *date)
						kontrolna++;
				}
			}

		kontrola:
			if (kontrolna >= 2)
			{
 				sukces++;
			}

		}
		if (n == 23) {
			printf("%d", sukces);
		}
		sukces = 0;
		n++;
	}
	printf("Paradoks zachodzi dla minimalnie %d osób", n + 1);
	return 0;
}