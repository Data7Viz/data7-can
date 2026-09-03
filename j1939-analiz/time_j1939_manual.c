#include <stdio.h>
#include <stdint.h>
#include <math.h> 
#define GRIN "\033[0;32m"
#define SIN "\033[0;34m"
#define GOT "\033[0;33m"
#define GR "\033[0;90m"
#define RES "\033[0m"

void tichina (double time, double prochl_time, uint32_t id, uint32_t prochl_id)
{
	double zazor = (time - prochl_time) - 0.000500;
	printf (" %X %lf  %X\n", prochl_id, zazor, id);
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
	
	// память для логики  
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;	

	// длительность снятия лога 
	double start_time = 0.0, end_time = 0.0;
	uint32_t prochl_id = 0, read_frame = 0;	
	
	// переменные для анализа времени
	double frame_start = 0.0, frame_jmp = 0.0;
	double prochl_time = 0.0, zazor = 0.0; 
	uint32_t count_addr = 0, count_broad = 0, count_f002 = 0, count_f002_f002 = 0; 
	uint16_t prochl_data [8] = {0}, arr_f002 [65536] = {0}, arr_f002_f002 [65536] = {0};  


	while (fgets (byf_file, sizeof (byf_file), file))
	{
		// парсим очищвем логи
		for (int i = 0; i <= 7; i ++) data [i] = 0;
		sscanf (byf_file," (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", 
				&time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]);
		
		read_frame ++;
		end_time = time; // переменная для вычисления длительности лога конечное время 
		byte0 = (id >> 24) & 0xff; byte1 = (id >> 16) & 0xff; byte2 = (id >> 8) & 0xff; 
		byte3 = id & 0xff, pgn = (id >> 8) & 0xffff, prior = (id >> 26) & 7;  

		if (read_frame == 1) 
		{ 
			start_time = time; // переменная для вычисления длительности лога стартовое время 
			// frame_0 = ceil (start_time); обнуляю разряды после точки стартового сообщения
			frame_start = time;
			frame_jmp = frame_start + 0.1; // прыгаю на 1 секунду вперёд
		}   	
	
		if ((time >= frame_start) && (time <= frame_jmp)) 
		{
			short count_n = 0;
			count_n ++;		
			if (byte1 < 240) { count_addr ++; } 
			else { count_broad ++; }  

			if (prochl_time > 0.0)
			{
				zazor = (time - prochl_time) - 0.000500;
				printf (SIN"\t\t ID %08X "RES, prochl_id);
			      	for (short i = 0; i <= 7; i ++)
				{
					//printf (SIN"%02hX"RES, prochl_data [i]);
				}
				printf ("\n");	
				printf ("ТИШИНА СЕТИ %lf\n", zazor); 
				//printf (GRIN"\t\t ID %08X DATA "RES, id);
				for (short a = 0; a <= 7; a ++)
				{
					//printf (GRIN"%02hX"RES, data [a]);
				}
			       	//printf ("\n\n");	
			} 
			prochl_time = time;
			prochl_id = id;
			for (short j = 0; j <= 7; j ++)
			{
			prochl_data [j] = data [j];
			} 
		// if ((time >= frame_start)...) 
		
		if (pgn == 0xF002)
		{ 
			arr_f002 [count_f002] = count_f002;
			arr_f002_f002 [count_f002] = count_f002_f002; 
			count_f002 ++; 
			count_f002_f002 = 0;
			
		}
		else 
		{ 
			count_f002_f002 ++; 
		}
		} // if ((time >= frame_start)...) 	
	} // while 
	fclose (file);
	int16_t count_tabl = 0;
	for (int i = 0; i <= 65535; i ++)
	{
		if (arr_f002_f002 [i] > 0) 
		{	
			printf (""GRIN" | МЛС %-5u"RES" СБЩ %-3u", arr_f002 [i], arr_f002_f002 [i]);
			count_tabl ++; if (count_tabl % 8 == 0) printf ("\n"); 
		} 
	}
       	printf ("\n"); 	
	printf ("Анализируем %lf сек Адресных сообщений %u Вещательных сообщений %u Всего %u\n", 
			frame_jmp - frame_start, count_addr, count_broad, count_addr + count_broad); 
	 
	return 0;
} 	

