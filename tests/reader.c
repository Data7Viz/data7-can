#include <stdio.h>
#include <stdint.h>
int main (int argc, char *argv [])
{
	if (argc < 2)
	{
		printf (" Ошибка -> Укажи имя файла \n");
		return 1;
	}

	FILE *file = fopen (argv [1], "r");
	if (file == NULL)
	{
		printf (" Ошибка : не удалось открыть файл %s\n", argv [1]);
		return 1;
	}

	char buf_file [256] = {0};
	double time = 0.0;
	uint32_t id = 0;
	uint8_t data [8] = {0}; 

	fgets (buf_file, sizeof (buf_file), file);

	sscanf (buf_file, " %lf%x%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx", &time,&id,&data [0],&data [1],&data [2],&data [3],&data [4],&data [5],&data [6],&data [7]);
      
	printf (" %lf %x", time, id);
	for (int i = 0; i < 8; i ++)
	{
		printf (" %x", data [i]);
	} 
	printf ("\n");
	fclose (file);
	return 0;
} 	



