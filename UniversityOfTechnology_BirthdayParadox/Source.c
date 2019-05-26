#define _CRT_SECURE_NO_WARNINGS
#define foreach(idxtype, idxpvar, col, colsiz ) idxtype* idxpvar; for( idxpvar=col ; idxpvar < (col + (colsiz)) ; idxpvar++)
#define arraylen( ary ) ( sizeof(ary)/sizeof(ary[0]) )
#define DNI 364
#define PROBY 1

#include <stdio.h>
#include <stdlib.h>

int generujLosowaLiczbe(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

int losujDzien(void)
{
	return generujLosowaLiczbe(1, DNI + 1);
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
	size_t n = 1;
	int sukces = 0;

	while (sukces <= (PROBY / 2)) 
	{
		for (int i = 0; i < PROBY; i++) 
		{	
			int* ludzie = malloc(n * sizeof(int));
			for (int i = 0; i < n; i++)
				ludzie[i] = losujDzien();

			int kontrolna = 0;

			foreach (int, date, ludzie, arraylen(ludzie)) 
			{
				int size = arraylen(ludzie);
				printf("%d", size);
				for (int r = 0; r < size; r++)
				{
					if (&ludzie[r] == *date)
					{
						kontrolna++;
					}
				}
			}

			if (kontrolna >= 2)
			{
				sukces++;
			}
			ludzie = NULL;
		}

		sukces = 0;
		n++;
	}
	printf("Paradoks zachodzi dla minimalnie %d osób", n + 1);
	return 0;
}