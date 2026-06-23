#include <stdio.h>
int main ()
{ 
	int data [] = {1,4,0,0,0,4,3,9,7,7,6,6,6,8,10,11,4,13,12,11,13,11,14,14,5,18,18,18,34,45,11,1,5,7,8};
	int buf [256] = {0};
	int var = 0;
	int razm = sizeof (data) / sizeof(data[0]);
	for (int i = 0; i < razm; i ++)
	{
		var = data [i];
		buf [var] ++;
	}
	for (int j = 0; j < 256; j ++)
	{
		if (buf [j] > 0) 
		printf (" %d %d\n", j, buf [j]);
	} 
	return 0;
} 



