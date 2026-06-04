
#include <stdio.h>
#include <stdint.h>
#define SIN "\033[1;34m"
#define GRI "\033[1;32m"
#define YOT "\033[1;33m"
#define GOB "\033[1;36m"
#define RES "\033[0m"

// широковешательный заголовок (шапка)
int broad () 
{
	printf (SIN" 31 30 29 |  2  1  0  |  1  0  |  15 14 13 12 11 10 9  8     7  6  5  4  3  2  1  0  |  7  6  5  4  3  2  1  0  | Си \n"RES);
	printf (GRI"  byte0   | Приоритет |  Р  Ст |byte1      Формат        PGN   byte2   Расширение    |byte3 -> Адрес Источника  | BROADCAST\n"RES);
	printf (SIN" 32 31 30 |  3  2  1  |  1  1  |  16 15 14 13 12 11 10 9     8  7  6  5  4  3  2  1  |  8  7  6  5  4  3  2  1  | J1939\n"RES);
} 
// адресный заголовок (шапка)
int p2p ()
{
	printf (SIN" 31 30 29 |  28 27 26 | 25  24 |  7  6  5  4  3  2  1  0  |  7  6  5  4  3  2  1  0  |  7  6  5  4  3  2  1  0  | Си \n"RES);    
	printf (GRI"  byte0   | Приоритет |  Р  Ст |byte1       Формат        |byte2 -> Адрес назначения |byte3 -> Адрес Источника  | POINT-TO-POINT\n"RES);
	printf (SIN" 32 30 29 |  3  2  1  |  1  1  |  8  7  6  5  4  3  2  1  |  8  7  6  5  4  3  2  1  |  8  7  6  5  4  3  2  1  | J1939\n"RES);
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
	printf (YOT"0x%x  %d\n"RES, var_id, var_id);
	return 0;
} 

// широковещательный декодер ID
int decode_broad (uint32_t decode)
{
	uint8_t byte3 = decode & 0xFF;
	uint16_t byte1_2 = decode >> 8 & 0xFFFF;
	uint8_t byteP = decode >> 24 & 1;
	uint8_t byteR = decode >> 25 & 1;
	uint8_t byte0 = decode >> 26 & 7;
	printf (YOT"%17u %8u %2u %31u %40u\n\n"RES, byte0, byteR,byteP, byte1_2, byte3);
	return 0;
} 

// адресный декодер ID 
int decode_p2p (uint32_t decode)
{
	uint8_t byte3 = decode & 0xFF;
	uint8_t byte2 = decode >> 8 & 0xFF;
	uint8_t byte1 = decode >> 16 & 0xFF;
	uint8_t byteP = decode >> 24 & 1;
	uint8_t byteR = decode >> 25 & 1;
	uint8_t byte0 = decode >> 26 & 7;
	printf (YOT"%17u %8u %2u %15u %25u %28u\n\n"RES, byte0, byteR, byteP, byte1, byte2, byte3);
	return 0;
} 

int main ()
{
	uint32_t can_id = 0, broad_or_p2p = 0;
	while (scanf ("%i", &can_id) == 1)
	{	
	printf ("\n");	
	broad_or_p2p = can_id >> 16 & 0xFF;
	if (broad_or_p2p >= 240) { broad (); id_bit (can_id); decode_broad (can_id); } 
	else { p2p (); id_bit (can_id); decode_p2p (can_id); }
	}
	return 0;
} 

