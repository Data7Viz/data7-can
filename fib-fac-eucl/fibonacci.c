#include <stdio.h>
#define GRIN "\033[0;32m"
#define RES "\033[0m"
int main ()
{
	unsigned int a = 0, b = 1, res = 0, bit = 0, count = 28, id = 0x0CF00400, to_fib = 0;
	for (int i = 1; i <= 29; i ++)
	{
		res = a + b;
		b = a; 
		a = res;
		to_fib = res * 2;
		bit = (id >> count) & 1;	
		printf ("\t № %-2u bit %u "GRIN" | "RES" ряд - %-3u число = %-6u"GRIN" | "RES"пар - %-7u\n", count, bit, i, res, to_fib);
		count --;
		if (i == 3 || i == 5 || i == 13 || i == 21)
		{ 
			printf ("\n");
		} 
	} 
	printf (GRIN"\t\t\t\t%X\n"RES, id); 
	return 0;
} 

