
#include <stdio.h>
#include <stdint.h>
#define SIN "\033[0;34m"
#define GRI "\033[1;32m"
#define YOT "\033[0;33m"
#define GOB "\033[0;36m"
#define RES "\033[0m"

// широковешательный заголовок (шапка)
int broad () 
{
	printf (SIN" 31 30 29 |  28 27 26 |  25 24 |  23 22 21 20 19 18 17 16   15 14 13 12 11 10  9  8  |  7  6  5  4  3  2  1  0  | Си \n"RES);
	printf (GRI"  byte1   | Приоритет |  Р  Ст |byte2      Формат        PGN   byte3   Расширение    |byte4 -> Адрес Источника  | BROADCAST\n"RES);
	printf (SIN"  -  -  - |  3  2  1  |  1  1  |  16 15 14 13 12 11 10 9     8  7  6  5  4  3  2  1  |  8  7  6  5  4  3  2  1  | J1939\n"RES);
} 
// адресный заголовок (шапка)
int p2p ()
{
	printf (SIN" 31 30 29 |  28 27 26 | 25  24 |  23 22 21 20 19 18 17 16 | 15 14 13 12 11 10  9  8  |  7  6  5  4  3  2  1  0  | Си \n"RES);    
	printf (GRI"  byte1   | Приоритет |  Р  Ст |byte2       Формат        |byte3 -> Адрес назначения |byte4 -> Адрес Источника  | POINT-TO-POINT\n"RES);
	printf (SIN"  -  -  - |  3  2  1  |  1  1  |  8  7  6  5  4  3  2  1  |  8  7  6  5  4  3  2  1  |  8  7  6  5  4  3  2  1  | J1939\n"RES);
} 

// разлаживаем ID на биты
int id_bit (uint32_t var_id)
{
	for (int i = 31; i >= 0; i --) 
	{
		int bin_id = (var_id >> i) & 1;
		if (bin_id == 1) { printf (YOT" 1 "RES); }
		else { printf (" 0 "); } 
		if (i % 8 == 0 || i % 26 == 0 || i % 29 == 0)
		{
		printf (YOT" | "RES);
		}
	} 
	printf (YOT"0x%x  %d\n\n"RES, var_id, var_id);
	return 0;
} 


int main ()
{
	uint32_t can_id_b = 0x0CF00400;
	uint32_t can_id_p = 0x18EA0300;
	printf ("\n\n");	
	broad ();
	id_bit (can_id_b);
	printf("\n\n");
	p2p ();
	id_bit (can_id_p);
	printf ("\n\n");
	
} 

