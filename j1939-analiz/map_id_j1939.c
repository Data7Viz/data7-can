#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[0;32m"
#define SIN "\033[0;34m"
#define GOT "\033[0;33m"
#define GR "\033[0;90m"
#define RES "\033[0m"

void print (char *cvet, char *stroka)
{
	printf ("%s%s---------------------------------------------------------------------------------------------------\n\n"RES,cvet,stroka);
} 
// функция для анализа 0,1,2,3 байта 
void fyn_for_byt1_byt2_byt3 (uint32_t *arr, char *str)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf (""GR" |"RES" %s"SIN" %-2X"RES" "GRIN"%-3u"RES" сбщ %-7u", str, i, i, arr [i]);
			a ++; if (a % 6 == 0) printf ("\n"); } 
	}
} 

// функция вещательные сообщения 
void fyn_pgn (uint32_t *arr_prior, uint32_t *arr_pgn, uint32_t *pgn_sour, double *pgn_start, double *pgn_end, double start_time, double end_time, uint32_t min, uint32_t max)
{
	int b = 0;
	for (int i = min; i <= max; i ++) 
	{ 
			if (arr_pgn [i] > 0)  
			{	
				double zaz_lv = pgn_start [i] - start_time;
				double zaz_pr = end_time - pgn_end [i]; 
				printf (""GR" |"RES""GRIN" п "RES"%u"SIN" %4X"RES" %-5u "GRIN" б "RES"%-3u "GRIN"с "RES"%-7u "GRIN"лв "RES"%-6.3lf "GRIN"пр "RES"%-6.3lf", arr_prior [i], i, i, pgn_sour [i], arr_pgn [i], zaz_lv, zaz_pr); 
				b ++; if (b % 3 == 0) printf ("\n"); 
			} 
		
	}
} 

// функция сообщения с блока на блок
void fyn_su_dt (uint32_t su_dt [256] [256])
{
	int c = 0;
	for (int i = 0; i <= 255; i ++)
	{
		for (int j = 0; j <= 255; j ++)
		{
			if (su_dt [i] [j] > 0)
			{
				printf (""GR" |"RES" ис"SIN" %-2X"RES" наз"SIN" %-2X "RES" сбщ %-7u", i, j, su_dt [i] [j]); 
				c ++; if (c % 6 == 0) printf ("\n");
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
	uint16_t a = 0;
	uint32_t all_frame = 0; // все фреймы 
	uint32_t read_frame = 0; // прочитаные фрейьы
	uint32_t kol_poter_frame = 0; // потеряные фреймы 
	// память для логики 
	uint32_t pgn_sour [65536] = {0}, arr_byte1 [256] = {0}, arr_byte2 [256] = {0}, arr_byte3 [256] = {0}, arr_br_byte3 [256] = {0}, arr_pgn [65536] = {0}, arr_prior [65536] = {0}, arr_sour_dist [256] [256] = {0}; 
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;	
	// счётчики вещательных и адресных сообщений общее колличество
	uint32_t count_br = 0, count_addr = 0;
	// длительность снятия лога 
	double start_time = 0.0, end_time = 0.0;
	// переменные для тайминга
	double pgn_start [65536] = {0.0}, pgn_end [65536] = {0.0};

	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы
		// парсим очищвем логи
		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file," (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10)
		{
		end_time = time;
		read_frame ++;
		byte0 = (id >> 24) & 0xff; byte1 = (id >> 16) & 0xff; byte2 = (id >> 8) & 0xff; byte3 = id & 0xff, pgn = (id >> 8) & 0xffff, prior = (id >> 26) & 7;  
		
		if (read_frame == 1) { start_time = time; }  
		
		// все блоки сети
		arr_byte3 [byte3] ++; 
		// адресные
		if (byte1 < 240) { 
			arr_prior [pgn] = prior; arr_byte1 [byte1] ++; arr_sour_dist [byte3] [byte2] ++; count_addr ++;}  	

		// вещательное
		else { 
			arr_prior [pgn] = prior; 
			arr_br_byte3 [byte3] ++; 
			arr_pgn [pgn] ++;
		        pgn_sour [pgn] = byte3;	
			count_br ++;}
			
		if (pgn_start [pgn] == 0.0 || time < pgn_start [pgn]) pgn_start [pgn] = time;

		if (pgn_end [pgn] == 0.0 || time > pgn_end [pgn]) pgn_end [pgn] = time; 


		} 
		else { printf ("Не прочитаные : %s", byf_file); } 
	} 
	fclose (file);
	kol_poter_frame = all_frame - read_frame;
	double dlitel_log = end_time - start_time; 
	
	printf ("\n");
	print (GOT, "[ Байт 1 ] Сетевые / Транспортные ---------------------------------"); fyn_for_byt1_byt2_byt3 (arr_byte1, "byte 1");
	printf ("\n\n");

	print (GOT, "[ Байт 2 ] Блоки источники вещательных сообщений [ байт 1 >= 240 ] "); fyn_for_byt1_byt2_byt3 (arr_br_byte3, "бл ист");
        printf	 ("\n\n");

	print (GOT, "[ Байт 3 ] Все блоки источники ------------------------------------"); fyn_for_byt1_byt2_byt3 (arr_byte3, "бл ист");
        printf ("\n\n"); 	

	print (GOT, "[ Байт 2 Байт 3 ] Сообщение с блока на блок [ byte 1 < 240 ] ------"); fyn_su_dt (arr_sour_dist);
	printf ("\n\n");

	//print (GOT, "[ байт 2 Байт 3 ] Адресные сообщения [ byte 1 < 240 ] -------------"); fyn_pgn (arr_prior, arr_pgn, 0, 61439);
	//printf ("\n\n");
	
	print (GOT, "[ Байт 1 Байт 2] Вещательные сообщения [ byte 1 >= 240 ] ----------"); fyn_pgn (arr_prior, arr_pgn, pgn_sour, pgn_start, pgn_end, start_time, end_time, 61440, 65279);
	printf ("\n\n");

	print (GOT, "[ Байт 1 Байт 2 ] Заводские Проприетарные [ byte 1 >= 240 ] -------"); fyn_pgn (arr_prior, arr_pgn, pgn_sour, pgn_start, pgn_end, start_time, end_time, 65280, 65535);
	printf ("\n\n");
	
	printf (GRIN"Всего %-7u Прочитано %-7u Пропущено %-7u"RES" "GOT" Длительность лога %-7lf сек"RES, all_frame, read_frame, kol_poter_frame, dlitel_log);
	printf (SIN"\tВещательных %-7u  Адресных %-7u\n"RES, count_br, count_addr);
	return 0;
} 	

