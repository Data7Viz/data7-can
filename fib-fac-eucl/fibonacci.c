#include <stdio.h>
#define GRIN "\033[0;32m"
#define RES "\033[0m"
void print ()
{
	printf (GRIN"\t     bit | ряд    число  |  пара     |  del    | del \n"RES);
} 
int main ()
{
	double a = 0, b = 1, res = 0, del = 0, to_fib = 0, del1 = 0; 
	unsigned int count = 28, id = 0x0CF00400, bit = 0;
	print (); 
	for (int i = 1; i <= 29; i ++)
	{
		res = a + b;
		del = b / a; 
		del1 = a / b;
		b = a; 
		a = res;
		to_fib = res * 2;
		bit = (id >> count) & 1;	
		printf ("\t %-2u   %u "GRIN" | "RES" %-3u   %-6.0lf"GRIN" | "RES"  %-7.0lf "GRIN"|"RES" %-7.4lf "GRIN"|"RES" %-4.4lf\n", count, bit, i, res, to_fib, del, del1);
		count --;
		if (i == 3 || i == 5 || i == 13 || i == 21)
		{ 
			printf ("\n");
		} 
	} 
	printf (GRIN"\t\t\t\t%X\n"RES, id); 
	return 0;
} 

