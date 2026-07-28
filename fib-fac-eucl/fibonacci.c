#include <stdio.h>
#define GRIN "\033[0;32m"
#define RES "\033[0m"
int main ()
{
	unsigned int a = 0, b = 1, res = 0, fib_num = 0, bit = 0, count = 28, id = 0x0CF00400;
	printf ("Введи число Фибонначчи : ");
	scanf ("%u", &fib_num);
	printf ("\n");
	for (int i = 1; i <= fib_num; i ++)
	{
		res = a + b;
		b = a; 
		a = res;
		bit = (id >> count) & 1;	
		printf ("\t %-2u bit %u "GRIN" | "RES" ряд %-3u число = %u\n", count, bit, i, res);
		count --;
		if (i == 3 || i == 5 || i == 13 || i == 21)
		{ 
			printf ("\n");
		} 
	} 
	return 0;
} 

