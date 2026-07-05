#define SIN "\033[38;5;73m"
#define GRIN "\033[38;5;150m"
#define YOT "\033[1;33m"
#define RED "\033[38;5;167m"
#define RES "\033[0m" 
#include <stdio.h>
#include <stdint.h>

// разлаживаем ID на биты
void id_bit (uint32_t var_id)
{
	for (int i = 28; i >= 0; i --) 
	{
		int bin_id = (var_id >> i) & 1; if (bin_id == 1)  printf (SIN" 1"RES); 
		else { printf (" 0"); }  if (i % 8 == 0 || i % 26 == 0) printf (YOT" |"RES);
	}
} 

// разлаживаем данные на биты
void data_bit (uint16_t *var_data)
{
	printf ("   ");
	for (int i = 0; i <= 7; i ++)
	{
		for (int j = 7; j >= 0; j --)
		{
			int bit = (var_data [i] >> j) & 1;
			if (bit == 1) printf (SIN"1"RES);
		        else printf ("0");
		}
		printf (YOT" | "RES);
	}
	printf ("\n\n");
}

// данные в HEX
void data_hex (uint16_t *arr_data)
{
	printf ("\033[91G");
	for (int i = 0; i <= 7; i ++)
	{
		printf (GRIN"   %-8X"RES, arr_data [i]);
	}
	printf ("\n");
} 

// функция разделяем HEX id на части 
void hex_id (uint32_t var_data)
{
	uint32_t byte1 = (var_data >> 16) & 0xFF, byte2 = (var_data >> 8) & 0xFF, byte3 = var_data & 0xFF;
	printf (GRIN"\033[9G%30u %6X  %10X  %15X "RES, byte1, byte1, byte2, byte3); 	 
} 

// функция в функции  
void fyn_fyn (uint32_t var_count, double time_time, uint32_t id_id, uint16_t *data_data) 
{
	uint32_t byte1 = (id_id >> 16) & 0xFF;
	if (byte1 < 240)
	{
		printf (GRIN" %u "RES, var_count); hex_id (id_id); data_hex (data_data);
	        printf (RED" %lf "RES, time_time); id_bit (id_id); data_bit (data_data); 
		
	}
	else 
	{
		printf (GRIN" %u "RES, var_count); hex_id (id_id); data_hex (data_data); 
		printf (RED" %lf "RES, time_time); id_bit (id_id); data_bit (data_data);
	        
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

	char buf_file [256] = {0};
	double time = 0.0;
	uint32_t id = 0;
	uint16_t data [8] = {0}; 

	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, line_counter = 0; 
	uint16_t line_print = 0;
	while (fgets (buf_file, sizeof (buf_file), file)) { 
	line_counter ++; // счётчик прочитаных фреймов 
	for (int i = 0; i <= 7; i ++) { data [i] = 0xFF; } // очищаем поле данных  
	sscanf (buf_file, " (%lf) %*s %X [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data [0],&data [1],&data [2],&data [3],&data [4],&data [5],&data [6],&data [7]);
	// фильтр пргораммы 
	pgn = (id >> 8) & 0xFFFF;
	if (pgn == 0xFECA) 
	{	
	fyn_fyn (line_counter, time, id, data); // вызов основной функции 
	// читаем по 10 строк 
	line_print ++;
	if (line_print >= 10) { getchar (); line_print = 0; } 
	} 
	} // закр скобки while 
fclose (file);
return 0;	
} 























