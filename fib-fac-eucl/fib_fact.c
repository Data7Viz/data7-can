#include <stdio.h>
int main ()
{
	unsigned int fib_a = 0, fib_b = 1, fib_res = 0, fact = 1;
	for (int i = 1; i <= 10; i ++)
	{
		fib_res = fib_a + fib_b;
		fib_b = fib_a; 
		fib_a = fib_res;
		fact *= i;
		printf ("\tряд %-3u Число Фибоначчи = %-15u  n!  %-3u = %u\n", i, fib_res, i, fact);
	} 
	return 0;
} 

