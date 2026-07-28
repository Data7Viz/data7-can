#include <stdio.h>
int main ()
{
	unsigned int fact_num = 0, res = 1;
	printf ("Введи число, чтобы вычислить его факториал : ");
	scanf ("%u", &fact_num); 
	for (int i = 1; i <= fact_num; i ++)
	{
		res *= i;
		printf (" %u! = %u\n", i, res);
	} 
	return 0;
} 
