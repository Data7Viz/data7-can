#include <stdio.h>
int main ()
{
	unsigned int a = 0, res = 1;
	for (int i = 1; i <= 8; i ++)
	{
		res *= i;
		printf (" %u! = %u\n", i, res);
	} 
	return 0;
} 
