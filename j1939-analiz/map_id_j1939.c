#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[0;32m"
#define SIN "\033[1;34m"
#define GOL "\033[0;33m"
#define RES "\033[0m"
void print (char *cvet, char *stroka)
{
	printf ("%s%-30s============================================================================================================================================================%s\n", cvet, stroka, RES);
} 
// функция для анализа или 0 или 1 или 2 или 3 байта 
void fyn_for_byt1_byt2_byt3 (uint32_t *arr)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf ("%-2X  сооб >  %-12u", i, arr [i]);
			a ++; if (a % 8 == 0) printf ("\n"); } 
	}
} 
// функция адрес источника адрес назначения 
void fyn_sour_dist (uint32_t arr [256] [256])
{
	int b = 0;
	for (uint32_t i = 0; i <= 255; i ++)
	{
		for (uint32_t j = 0; j <= 255; j ++)
		{
			if (arr [i] [j] > 0)
			{
				printf ("%-2X -> %-2X сооб > %-8u", i, j, arr [i] [j]);
				b ++; if (b % 8 == 0) printf ("\n");
			}
		}
	} 
} 	


// PGN параметрические диагностические 
void fyn_pgn (uint32_t *arr_p, uint32_t *arr_prior, uint32_t min, uint32_t max)
{
	int c = 0;
	for (int i = min; i <= max; i ++) 
	{  
		if (arr_p [i] > 0)
		{	
				printf ("p %-2u %-5u   %-4X ->  %-8u", arr_prior [i], i, i, arr_p [i]); 
				c ++; if (c % 6 == 0) printf ("\n"); 
		} 
	} 
} 


int main (int argc, char *argv [])
{
	if (argc < 2) { printf (" Ошибка -> Укажи имя файла \n"); return 1; }

	FILE *file = fopen (argv [1], "r");
	if (file == NULL) { printf (" Ошибка : не удалось открыть файл %s\n", argv [1]); return 1; }
	// память для парсера 		
	char byf_file [256] = {0}; 
	double time = 0.0;
	uint32_t id = 0;
	uint16_t data [8] = {0};

	uint32_t all_frame = 0; // все фреймы 
	uint32_t read_frame = 0; // прочитаные фрейьы
	uint32_t kol_poter_frame = 0; // потеряные фреймы 
	// память для логики 
	uint32_t arr_tcp_data [256] [256] = {0}, arr_tcp_connect [256] [256] = {0}, arr_prior [65536] = {0}, arr_pgn [65536] = {0}, arr_sour_dist [256] [256] = {0};
	uint32_t arr_byte1 [256] = {0}, arr_byte2 [256] = {0}, arr_byte3 [256] = {0}, arr_dist [256] = {0};
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;
	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы
		// парсим очищвем логи
		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file, " (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10);
		{
		read_frame ++;
		byte0 = (id >> 24) & 0xff; byte1 = (id >> 16) & 0xff; byte2 = (id >> 8) & 0xff; byte3 = id & 0xff, pgn = (id >> 8) & 0xffff, prior = (id >> 26) & 7;  
		arr_byte1 [byte1] ++;
		arr_byte2 [byte2] ++;
		arr_byte3 [byte3] ++; 
		// сообщение с блока на блок
		if (byte1 < 240) { arr_dist [byte2] ++; arr_sour_dist [byte3] [byte2] ++; arr_pgn [pgn] ++; arr_prior [pgn] = prior; }  

		else { arr_pgn [pgn] ++; arr_prior [pgn] = prior; }
		} 
    		
	} 
	fclose (file);
	
	print (SIN, "byte1 ========================="); fyn_for_byt1_byt2_byt3 (arr_byte1);
	printf ("\n\n");

	print (GRIN, "byte2 ========================"); fyn_for_byt1_byt2_byt3 (arr_byte2);
	printf ("\n\n");
	
	print (SIN, "byte3 все  блоки   источники =="); fyn_for_byt1_byt2_byt3 (arr_byte3);
	printf ("\n\n"); 

	print (GRIN, "byte2 все  блоки  назначения ="); fyn_for_byt1_byt2_byt3 (arr_dist);
	printf ("\n\n");
	
        print (SIN, "Сообщения с блока >> на блок =="); fyn_sour_dist (arr_sour_dist);
	printf ("\n\n");
	
	print (GRIN, "Адресные           сообщения ="); fyn_pgn (arr_pgn, arr_prior, 0, 61439);
	printf ("\n\n");	
	
        print (SIN, "Вещательные   сообщение  PGN =="); fyn_pgn (arr_pgn, arr_prior, 61440, 65535);
	printf ("\n\n");

	print (GRIN, "Диагностическое    сообщение ="); fyn_pgn (arr_pgn, arr_prior, 65226, 65237);
	printf ("\n");
	
	// КОЛЛИЧЕСТВО прочитаных фрейьов
	kol_poter_frame = all_frame - read_frame;
	printf (GOL"Всего %-15u Прочитано %-15u Пропущено %-15u\n"RES, all_frame, read_frame, kol_poter_frame);
	printf ("\n");
	return 0;
} 	

