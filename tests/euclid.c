#include <stdio.h>
int main ()
{
	unsigned int a = 0, b = 0, res = 0;
	scanf ("%u %u", &a, &b);
	while (b != 0)
	{
		res = a % b;
		a = b;
		b = res;
	}
	printf ("\n");
	printf (" НОД = %u\n", a);
	return 0;
}  

