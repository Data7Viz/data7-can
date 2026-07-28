#include <stdio.h>
int main ()
{
	unsigned int a = 0, b = 1, res = 0;
	for (int i = 1; i <= 29; i ++)
	{
		res = a + b;
		b = a; 
		a = res;
		printf ("%u\n", res);
	} 
	return 0;
} 

