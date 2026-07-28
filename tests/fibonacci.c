#include <stdio.h>
int main ()
{
	unsigned int a = 0, b = 1, res = 0, fib_num = 0;
	scanf ("%u", &fib_num);
	for (int i = 1; i <= fib_num; i ++)
	{
		res = a + b;
		b = a; 
		a = res;
		printf ("%u\n", res);
	} 
	return 0;
} 

