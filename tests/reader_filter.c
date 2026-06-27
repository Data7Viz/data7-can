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
	uint16_t data [8] = {0};
	uint32_t buf_analize [65536] = {0};
	uint32_t all_string = 0;
	uint32_t poisk = 0;
	uint32_t read_string = 0;
	uint32_t kol_poter_string = 0;
	while (fgets (buf_file, sizeof (buf_file), file))
	{
		all_string ++;
		if (sscanf (buf_file, " (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10);
		{
         	poisk = id & 0xff;
		buf_analize [poisk] ++;
	        read_string ++;	
		} 
	} 
	fclose (file);
	
	printf ("\n");
	for (int i = 0; i <= 65535; i ++)
	{
		
		if (buf_analize [i] > 0)
		{
			printf (" номер блока %X   \t  отправленно сообщений %u\n", i, buf_analize [i]);

		}
	}
	printf ("\n");
	kol_poter_string = all_string - read_string;
	printf (" Всего сообщений \t %u\n", all_string);
	printf (" Прочитаные сообщения \t %u\n", read_string);	
	printf (" Пропущенно  сообщений \t %u\n", kol_poter_string);
	return 0;
} 	



