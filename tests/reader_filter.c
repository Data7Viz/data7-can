#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[0;32m"
#define SIN "\033[0;34m"
#define GOL "\033[0;33m"
#define RES "\033[0m"
void cikl1 (uint32_t *arr)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf ("Блок %-2X сообщений %-12u", i, arr [i]);
			a ++; if (a % 6 == 0) printf ("\n"); } 
	}
} 

void cikl2 (uint32_t *arr, uint32_t a, uint32_t b)
{
	int d = 0;
	for (int i = 0; i <= 65535; i ++) 
	{ 
		if (arr [i] > 0)
		{	
			if (i >= a &&  i <= b)
			{
				printf (" pgn %-2X  %-2d  -> %-10u", i, i, arr [i]); 
				d ++; if (d % 6 == 0) printf ("\n");
			} 
		} 
	} 
} 
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
		
	char byf_file [256] = {0}; 
	double time = 0.0;
	uint32_t id = 0;
	uint16_t data [8] = {0};
	uint32_t mas_byte3 [256] = {0};

	uint32_t all_frame = 0; // все фреймы 
	uint32_t byte3 = 0; // переменная для адресного 3 байт ID 
	uint32_t read_frame = 0; // прочитаные фрейьы
	uint32_t kol_poter_frame = 0; // потеряные фреймы 
	// переменные для 1 байта
	uint32_t mas_byte1_p2p [256] = {0};
	uint32_t mas_byte1_br [256] = {0};
	uint16_t byte1 = 0;
	uint32_t p2p = 0;
	uint32_t brodcas = 0;
	// PGN
	uint32_t mas_byte1_2 [65536] = {0};
	uint32_t byte1_2 = 0;
	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы

		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file, " (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10);
		{
		// анализируем 3 адресный байт ID какие блоки в сети колличество сообщений с каждого блока
         	byte3 = id & 0xff; 
		mas_byte3 [byte3] ++;
	        read_frame ++;	// прочитаные фреймы 
		} 
		// анализируем 1 байт ID вещательный или адресный колличество вещат и адрес сообщений 
		byte1 = (id >> 16) & 0xff;
		if (byte1 < 240) { mas_byte1_p2p [byte1] ++; p2p ++; }
		
		if (byte1 >= 240) { mas_byte1_br [byte1] ++; brodcas ++; } 
		// PGN
		byte1_2 = (id >> 8) & 0xffff;
		if (byte1_2 >= 61440) { mas_byte1_2 [byte1_2] ++; } 
	        	
	} 
	fclose (file);
	
	printf ("\n");
	
	// все блоки в сети и колличество сообщений с каждого блока
	printf (GRIN"================================================================================ Все сообщения =================================================================================\n"RES); 
	cikl1 (mas_byte3); // вызов функции 

        kol_poter_frame = all_frame - read_frame; // вычисляем колличество не прочитаных сообщений

	printf ("\n"); 	
	printf (GRIN"\t\t\tВсего сообщений  %-15u"RES, all_frame);
	printf (GRIN"\tПрочитано сообщений  %-15u"RES, read_frame);
	printf (GRIN"\tПропущенно сообщений  %-15u\n\n"RES, kol_poter_frame);
	
	// все адресные сообщения и колличество сообщений с каждого блока
	printf (SIN"============================================================================ Адресныe сообщений =================================================================================\n"RES);
	cikl1 (mas_byte1_p2p);
	printf ("\n");	
	printf (SIN"\t\t\t\t\t\t\t\t\t\tВсего Сообщений %u\n\n"RES, p2p);
	
	// все вещательные сообщения и колличество сообщений с каждого блока
	printf (GOL"====================================================================== Широковещательные сообщения ==============================================================================\n"RES); 
	cikl1 (mas_byte1_br);	
	printf ("\n");
	printf (GOL"\t\t\t\t\t\t\t\t\t\tВсего Сообщений %u\n\n"RES, brodcas);
	
	// PGN параметрические
	printf (GRIN"======================================================================== Параметрические =======================================================================================\n"RES);
	cikl2 (mas_byte1_2, 61440, 65087);
	printf ("\n\n");
	
	// PGN диагностические 
	printf (SIN"======================================================================== Диагностические ========================================================================================\n"RES);
	cikl2 (mas_byte1_2, 65088, 65279); 
	printf ("\n\n");
	
	// PGN свободные 
	printf (GOL"======================================================================= Свободные ===============================================================================================\n"RES);
	cikl2 (mas_byte1_2, 65280, 65535); 
	printf ("\n\n");
	
	return 0;
} 	

