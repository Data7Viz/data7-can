#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[0;32m"
#define SIN "\033[0;34m"
#define GOT "\033[0;33m"
#define RED "\033[0;31m"
#define RES "\033[0m"

void print (char *cvet, char *stroka)
{
	printf ("%s%s-------------------------------------------------------------------------------------------------------------------------------------------------\n"RES,cvet,stroka);
} 
// функция для анализа 0,1,2,3 байта 
void fyn_for_byt1_byt2_byt3 (uint32_t *arr, char *stroka2)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf (SIN" %-2X"RES" "GRIN"%-3u"RES" %s "GRIN"%-12u"RES, i, i, stroka2, arr [i]);
			a ++; if (a % 6 == 0) printf ("\n"); } 
	}
} 

// функция адресные вещательные сообщения 
void fyn_pgn (uint32_t *arr_prior, uint32_t *arr, uint32_t min, uint32_t max)
{
	int b = 0;
	for (int i = min; i <= max; i ++) 
	{ 
		if (arr [i] > 0)
		{	
				printf ("  %u "GOT" |"RES"  "SIN"%4X"RES"   "GRIN"%-5u"RES""GOT" |"RES" "GRIN"%-7u"RES"", arr_prior [i], i, i, arr [i]); 
				b ++; if (b % 6 == 0) printf ("\n"); 
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
				printf (" с >>"SIN" %-2X"RES" на >>"SIN" %-2X "RES"сообщ %-7u", i, j, su_dt [i] [j]); 
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
	uint32_t arr_byte1 [256] = {0}, arr_byte2 [256] = {0}, arr_byte3 [256] = {0}, arr_pgn [65536] = {0}, arr_prior [65536] = {0}, arr_sour_dist [256] [256] = {0}, arr_dist [256] = {0}; 
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;	
	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы
		// парсим очищвем логи
		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file," (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10)
		{
		read_frame ++;
		byte0 = (id >> 24) & 0xff; byte1 = (id >> 16) & 0xff; byte2 = (id >> 8) & 0xff; byte3 = id & 0xff, pgn = (id >> 8) & 0x3ffff, prior = (id >> 26) & 7;  
		// все блоки сети 
		arr_byte1 [byte1] ++;
		arr_byte2 [byte2] ++;
		arr_byte3 [byte3] ++; 
		// адресные
		if (byte1 < 240) { 
			arr_prior [pgn] = prior; 
			arr_pgn [pgn] ++; 
			arr_sour_dist [byte3] [byte2] ++;
			arr_dist [byte2] ++; 
		}  	

		// вещательное
		else { arr_prior [pgn] = prior; arr_pgn [pgn] ++; }
		} 
		else { printf ("Не прочитаные : %s", byf_file); } 
    		
	} 
	fclose (file);
	
	print (GOT, "байт 1 ----------"); fyn_for_byt1_byt2_byt3 (arr_byte1, "сооб");
	printf ("\n\n");

	print (GOT, "байт 2 ----------"); fyn_for_byt1_byt2_byt3 (arr_byte2, "сооб");
	printf ("\n\n");

	print (GOT, "Байт 3 все адреса источники "); fyn_for_byt1_byt2_byt3 (arr_byte3, "сооб");
	printf ("\n\n");

	print (GOT, "Байт 2 все адреса назначения "); fyn_for_byt1_byt2_byt3 (arr_dist, "сооб");
        printf ("\n\n"); 	

	print (GOT, "Адресные с блока на >> блок байт2 << байт3 "); fyn_su_dt (arr_sour_dist);
	printf ("\n\n");

	print (GOT, "Адресные байт1 байт2 "); fyn_pgn (arr_prior, arr_pgn, 0, 61439);
	printf ("\n\n");
	
	print (GOT, "Вещательные байт1 байт2 ");  fyn_pgn (arr_prior, arr_pgn, 61440, 65279);
	printf ("\n\n");

	print (GOT, "Заводские -------"); fyn_pgn (arr_prior, arr_pgn, 65280, 65535);
	printf ("\n");
	 
	
	// КОЛЛИЧЕСТВО прочитаных фреймов
	kol_poter_frame = all_frame - read_frame;
	printf (GOT"Всего %-15u Прочитано %-15u Пропущено %-15u\n"RES, all_frame, read_frame, kol_poter_frame);
	printf ("\n");
	return 0;
} 	

