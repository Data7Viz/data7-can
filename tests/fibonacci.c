#include <stdio.h>
int main ()
{
	unsigned int a = 0, b = 1, res = 0, fib_num = 0;
	printf ("Введи число Фибонначчи : ");
	scanf ("%u", &fib_num);
	printf ("\n");
	for (int i = 1; i <= fib_num; i ++)
	{
		res = a + b;
		b = a; 
		a = res;
		printf ("%-3u число Фибоначчи = %u\n", i, res);
	} 
	return 0;
} 

