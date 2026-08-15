#include <stdio.h>
#include <stdint.h>
#include <math.h> 
#define GRIN "\033[0;32m"
#define SIN "\033[0;34m"
#define GOT "\033[0;33m"
#define GR "\033[0;90m"
#define RES "\033[0m"

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
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;	

	// длительность снятия лога 
	double start_time = 0.0, end_time = 0.0;
	uint32_t prochl_id = 0;	
	
	// переменные для анализа времени
	double frame_0 = 0.0, frame_jmp = 0.0;
	double prochl_time = 0.0, zazor = 0.0, max_zazor = 0.0; 
	uint32_t count_0_jmp = 0;

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
		
		if (read_frame == 1) 
		{ 
			start_time = time;
			// frame_0 = ceil (start_time); обнуляю разряды после точки стартового сообщения
			frame_0 = time;
			frame_jmp = frame_0 + 0.2; // прыгаю на 1 секунду вперё
		}   	
	
		if ((time >= frame_0) && (time <= frame_jmp)) 
		{
			
				if (prochl_time  > 0.0)
				{ 
				zazor = time - prochl_time; // вычисляем зазор между кадрами 
				printf (" %-5u "GRIN" %-8X"RES" зазор %-10lf"SIN"%-8X "RES, count_0_jmp, prochl_id, zazor, id); 
				
				count_0_jmp ++; // счётчик сообщений 
				
				if (count_0_jmp % 4 == 0) printf ("\n"); // отрисовка таблицы  
				}
					prochl_time = time; // берём прошлое время 
					prochl_id = id;
	   
		} 
		
		} 
		else { //printf ("Не прочитаные : %s", byf_file); 
		     } 
	} 
	fclose (file);
	double zagr_seti = ((count_0_jmp * 0.000500) / (frame_jmp - frame_0)) * 100.0;
	printf ("\t СООБЩЕНИЙ %u  ЗАГРУЗКА СЕТИ %lf\n", count_0_jmp, zagr_seti);
	 
	
	// КОЛЛИЧЕСТВО прочитаных фреймов
	kol_poter_frame = all_frame - read_frame;
	printf (GRIN"Всего %-7u Прочитано %-7u Пропущено %-7u"RES" "GOT" Длительность лога %-7lf\n сек"RES, all_frame, read_frame, kol_poter_frame, end_time - start_time);
	return 0;
} 	

