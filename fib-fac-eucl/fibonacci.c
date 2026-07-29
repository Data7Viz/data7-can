#include <stdio.h>
#define GRIN "\033[0;32m"
#define RES "\033[0m"
void print ()
{
	printf (GRIN"\t     bit | ряд    число  |  хэш fib \n"RES);
} 
int main ()
{
	unsigned int a = 0, b = 1, res = 0, fib = 0, byf_fib = 0; 
	unsigned int count = 28, id = 0, bit = 0;
	scanf (" %i", &id);
	print (); 
	for (int i = 1; i <= 29; i ++)
	{
		res = a + b;
		b = a; 
		a = res;
		bit = (id >> count) & 1;
		fib = bit * res;
		byf_fib += fib;
		printf ("\t %6u "GRIN" | "RES" %-3u   %-6.0u"GRIN" | "RES" %-5u\n", bit, i, res, fib);
		count --;
		if (i == 3 || i == 5 || i == 13 || i == 21)
		{ 
			printf ("\n");
		} 
	} 
	printf (GRIN"ID J1939 0x%X  %20u\n"RES, id, byf_fib); 
	 
	return 0;
} 

