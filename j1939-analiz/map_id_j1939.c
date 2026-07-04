#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[1;32m"
#define SIN "\033[0;34m"
#define GOL "\033[0;33m"
#define RES "\033[0m"
void print (char *cvet)
{
	printf ("%s---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"RES, cvet);
} 
// функция для анализа 0,1,2,3 байта 
void fyn_for_byt1_byt2_byt3 (uint32_t *arr, char *stroka1, char *stroka2)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf (" %s %-2X %s %-12u", stroka1, i, stroka2, arr [i]);
			a ++; if (a % 6 == 0) printf ("\n"); } 
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
				printf (" %-2X  -> %-2X  %-12u", i, j, arr [i] [j]);
				b ++; if (b % 6 == 0) printf ("\n");
			}
		}
	} 
} 	


// PGN параметрические диагностические 
void fyn_pgn (uint32_t *arr, uint32_t *arr_prior, uint32_t min, uint32_t max)
{
	int c = 0;
	for (int i = min; i <= max; i ++) 
	{ 
		if (arr [i] > 0)
		{	
				printf ("pri  %-2u pgn %-2X  -> %-10u", arr_prior [i], i, arr [i]); 
				c ++; if (c % 6 == 0) printf ("\n"); 
		} 
	} 
} 
// TCp
void fyn_tcp (uint32_t arr [256] [256])
{
	int d = 0;
	for (uint32_t i = 0; i <= 255; i ++)
	{
		for (uint32_t j = 0; j <= 255; j ++)
		{
			if (arr [i] [j] > 0)
			{
				printf (" %-3X  ->>   %-3X     %-10u", i, j, arr [i] [j]);
				d ++; if (d % 6 == 0) printf ("\n"); 
			}
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
	uint32_t arr_tcp_data [256] [256] = {0}, arr_tcp_connect [256] [256] = {0}, arr_byte2 [256] = {0}, arr_byte3 [256] = {0}, arr_pgn [65536] = {0}, arr_sour_dist [256] [256] = {0};
	uint32_t arr_prior [65536] = {0}; 
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;
	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы
		// парсим очищвем логи
		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file, " (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10);
		{
		read_frame ++;
		byte0 = (id >> 24) & 0xff; byte1 = (id >> 16) & 0xff; byte2 = (id >> 8) & 0xff; byte3 = id & 0xff, pgn = (id >> 8) & 0x3ffff, prior = (id >> 26) & 7;  
		// все блоки сети 
		arr_byte3 [byte3] ++;
		// TCP
		if (byte1 == 0xEC) { arr_tcp_connect [byte3] [byte2] ++; } 
		else if (byte1 == 0xEB) { arr_tcp_data [byte3] [byte2] ++; } 
		// сообщение с блока на блок
		else if (byte1 < 240) { arr_sour_dist [byte3] [byte2] ++; arr_pgn [pgn] ++; arr_prior [pgn] = prior; }  
		// pgn
		else { arr_pgn [pgn] ++; arr_prior [pgn] = prior; }
		} 
    		
	} 
	fclose (file);
	// все блоки отправители 
	printf (SIN"\t\tВсе блоки в сети\n"RES);
	fyn_for_byt1_byt2_byt3 (arr_byte3, "блок", "фреймы");
	printf ("\n"); 
	// сообщение с блока на блок 
	print (GRIN); printf (SIN"\t\tСообщение с блока >> на блок\n"RES);
	fyn_sour_dist (arr_sour_dist);
	printf ("\n");
	// TCP	
	print (GRIN); printf (SIN"\t\tTCP Запрос на подключение\n"RES);
	fyn_tcp (arr_tcp_connect); 		
	printf ("\n");
	print (GRIN); printf (SIN"\t\tTCP ответ данные\n"RES);
	fyn_tcp (arr_tcp_data);
	printf ("\n");	
	// PGN параметрические
	print (GRIN); printf (SIN"\t\tPGN параметрические\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 61440, 65087);
	printf ("\n");
	// PGN диагностические 
	print (GRIN); printf (SIN"\t\tPGN диагностические\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 65088, 65279); 
	printf ("\n");
	// PGN свободные 
	print (GRIN); printf (SIN"\t\tPGN проприетарные\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 65280, 65535);
        printf ("\n");	
	// диагностика и сервис
	print (GRIN); printf (SIN"\t\t\t\t\t\t\t\t\t\tРАЗДЕЛ ДИАГНОСТИКИ И СЕРВИСА\n"RES);
	printf (SIN"\t\tДИАГНОСТИКА Коды неисправностей (DM1 - DM5, DM25)\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 0xFE6D, 0xFECE);
	printf ("\n");
	// сервис 
	print (GRIN); printf (SIN"\t\tСЕРВИС Паспорта блоков и калибровок (DM11, DM19, DM24)\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 0xFE6F, 0xFED8);
	printf ("\n");
 	// системные
	print (GRIN); printf (SIN"\t\tСИСТЕМНЫЕ Запросы параметров и опрос сети (Request)\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 0xEA00, 0xEBFF);
	printf ("\n");
	print (GRIN); 
	// КОЛЛИЧЕСТВО прочитаных фрейьов
	kol_poter_frame = all_frame - read_frame;
	printf (GOL"Всего %-15u Прочитано %-15u Пропущено %-15u\n"RES, all_frame, read_frame, kol_poter_frame);
	printf ("\n");
	return 0;
} 	

