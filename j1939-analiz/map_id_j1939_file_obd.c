#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#define GRIN "\033[0;32m"
#define SIN "\033[0;34m"
#define GOT "\033[0;33m"
#define RED "\033[0;90m"
#define RES "\033[0m"

// функция для анализа 0,1,2,3 байта 
void fyn_for_byt1_byt2_byt3 (uint32_t *arr, char *str)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf (" %s"SIN" %-2X"RES" "GRIN"%-3u"RES" сбщ %-7u", str, i, i, arr [i]);
			a ++; if (a % 6 == 0) printf ("\n"); } 
	}
	printf ("\n\n\n\n");
} 

// функция адресные вещательные сообщения 
void fyn_pgn (uint32_t *arr_prior, uint32_t *arr, uint32_t min, uint32_t max)
{
	int b = 0;
	for (int i = min; i <= max; i ++) 
	{ 
		if (arr [i] > 0)
		{	
				printf (" %u"SIN" %4X"RES" "GRIN"%-5u"RES" сбщ %-7u ", arr_prior [i], i, i, arr [i]); 
				b ++; if (b % 6 == 0) printf ("\n"); 
		} 
	}
	printf ("\n\n\n\n");
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
				printf (" ис"SIN" %-2X"RES" наз"SIN" %-2X "RES" сбщ %-7u", i, j, su_dt [i] [j]); 
				c ++; if (c % 6 == 0) printf ("\n");
			}
		}
	}
	printf ("\n\n\n\n"); 
} 
int main (int argc, char *argv [])
{
	FILE *file;
	if (argc >= 2) 
	{ file = fopen (argv [1], "r");
	if (file == NULL) { printf (" Ошибка : не удалось открыть файл %s\n", argv [1]); return 1; }
	}
	else { file = stdin; } 

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
	uint32_t arr_byte1 [256] = {0}, arr_byte2 [256] = {0}, arr_byte3 [256] = {0}, arr_br_byte3 [256] = {0}, arr_pgn [65536] = {0}, arr_prior [65536] = {0}, arr_sour_dist [256] [256] = {0}; 
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;	
	uint32_t count_br = 0, count_add = 0;
	double start_time = 0.0, end_time = 0.0;
	
	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы
		// парсим очищвем логи
		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file," (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10)
		{
		end_time = time;
		read_frame ++;
		byte0 = (id >> 24) & 0xff; byte1 = (id >> 16) & 0xff; byte2 = (id >> 8) & 0xff; byte3 = id & 0xff, pgn = (id >> 8) & 0x3ffff, prior = (id >> 26) & 7;  
		
		if (read_frame == 1) { start_time = time; }  
		
		// все блоки сети
		arr_byte3 [byte3] ++; 
		// адресные
		if (byte1 < 240) { 
			arr_prior [pgn] = prior; arr_byte1 [byte1] ++; arr_pgn [pgn] ++; arr_sour_dist [byte3] [byte2] ++; count_add ++; 
		}  	

		// вещательное
		else { arr_prior [pgn] = prior; arr_br_byte3 [byte3] ++; arr_pgn [pgn] ++; count_br ++; } 

	printf ("\033[H\n"); 
	// fyn_for_byt1_byt2_byt3 (arr_byte1, "b1<204");
	
	// fyn_for_byt1_byt2_byt3 (arr_br_byte3, "вщ блк");

	// fyn_for_byt1_byt2_byt3 (arr_byte3, "все бл"); 

	// fyn_su_dt (arr_sour_dist);

	// fyn_pgn (arr_prior, arr_pgn, 0, 61439); 
	
	fyn_pgn (arr_prior, arr_pgn, 61440, 65279);

	// fyn_pgn (arr_prior, arr_pgn, 65280, 65535);
	
	}
	} 
	if (file != stdin) { fclose (file); }	
 	printf ("\n");	
	// КОЛЛИЧЕСТВО прочитаных фреймов
	kol_poter_frame = all_frame - read_frame;
	printf (GOT"Всего %-7u Прочитано %-7u Пропущено %-7u  Длительность лога %-7.0lf сек "RES, all_frame, read_frame, kol_poter_frame, end_time - start_time);
	printf (GOT"\tВещательных %-7u  Адресных %-7u фреймов \n", count_br, count_add);
	printf ("\n"); 	
	return 0;
} 	

