#define _CRT_SECURE_NO_WARNINGS
#define for_each(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)
#define DNI 364
#define PROBY 30000

#include <stdio.h>

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
	int* r;
	if (sizeof(r) > 0)
	{
		r = realloc(r, sizeof(int));
	}
	else
	{
		r = malloc(size * sizeof(int));
	}

	for (int i = 0; i < size; i++)
	{
		r[i] = losujDzien();
	}
	return r;
}

int main()
{
	int n = 1;
	int sukces = 0;
	
	while (sukces <= (PROBY / 2)) 
	{
		for (int i = 0; i < PROBY; i++) 
		{	
			int* ludzie = przydzielDaty(n);
			int kontrolna = 0;

			for_each(int* date, ludzie) 
			{
				int size = sizeof(ludzie) / sizeof(int);
				for (int r = 0; r < size; r++)
				{
					printf("%d", r);
					if (ludzie[r] == *date)
					{
						kontrolna++;
					}
				}
			}

			if (kontrolna >= 2)
			{
				sukces++;
			}
		}

		sukces = 0;
		n++;
	}
	printf("Paradoks zachodzi dla minimalnie %d osób", n + 1);
	return 0;
}