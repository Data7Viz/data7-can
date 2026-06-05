
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
	printf (GRI"    Pr | R Pg|      PF        PGN     PS         |    Src Addr     | "RES);
	printf (GRI" |   d1   |   d2     |    d3    |    d4    |    d5    |    d6    |    d7    |    d8    | \n"RES);	
	return 0;
} 
// адресный заголовок (шапка)
int p2p ()
{
	printf (GRI"    Pr | R Pg|      PF        p2p    Dst Adr     |   Src Addr      | "RES);
	printf (GRI" |  d1    |   d2     |    d3    |    d4    |    d5    |    d6    |    d7    |    d8    | \n"RES);
	return 0;
} 

// разлаживаем ID на биты
int id_bit (uint32_t var_id)
{
	for (int i = 28; i >= 0; i --) 
	{
		int bin_id = (var_id >> i) & 1;
		if (bin_id == 1) { printf (YOT" 1"RES); }
		else { printf (" 0"); } 
		if (i % 8 == 0 || i % 26 == 0)
		{
		printf (YOT" |"RES);
		}
	} 

	return 0;
} 

// разлаживаем DATA на биты
int data_bit (uint8_t *var_data)
{
	printf ("  ");
	for (int i = 0; i < 8; i ++) 
	{
		for (int bit = 7; bit >= 0; bit --)
		{
			if ((var_data [i] >> bit) & 1) { printf (YOT"1"RES); }
			else { printf ("0"); }
		}

		printf (" | "); 
	}
	printf ("\n");
	return 0;
} 

// выводим DEC данных
int data_dec (uint8_t *var_dec)
{
	printf ("     ");
	for (int i = 0; i <= 7; i ++)
	{
		printf ("%11d", var_dec [i]);
		
	}
	printf ("\n\n");
	return 0;
} 

// широковещательный декодер ID
int decode_broad (uint32_t decode)
{
	uint8_t byte3 = decode & 0xFF;
	uint16_t byte1_2 = decode >> 8 & 0xFFFF;
	uint8_t bitP = decode >> 24 & 1;
	uint8_t bitR = decode >> 25 & 1;
	uint8_t byte0 = decode >> 26 & 7;
	char *type = NULL;
	if (byte1_2 >= 0xF000 && byte1_2 <= 0xFE3F) type = "P";
	else if (byte1_2 >= 0xFE40 && byte1_2 <= 0xFEFF) type = "D";
	else if (byte1_2 >= 0xFF00 && byte1_2 <= 0xFFFF) type = "R";
	printf (SIN"%4u %5u %1u %7s %13u %24u"RES, byte0, bitR, bitP, type, byte1_2, byte3);
	return 0;
} 

// адресный декодер ID 
int decode_p2p (uint32_t decode)
{
	uint8_t byte3 = decode & 0xFF;
	uint8_t byte2 = decode >> 8 & 0xFF;
	uint8_t byte1 = decode >> 16 & 0xFF;
	uint8_t bitP = decode >> 24 & 1;
	uint8_t bitR = decode >> 25 & 1;
	uint8_t byte0 = decode >> 26 & 7;
	printf (SIN"%4u %5u %1u %11u %16u %17u"RES, byte0, bitR, bitP, byte1, byte2, byte3);
	return 0;
} 

int main ()
{
	uint32_t can_fr = 0, broad_or_p2p = 0;
	printf ("\n");
	scanf ("%i", &can_fr);
	uint8_t can_data [8] = {0xFF, 0x7D, 0xB4, 0x23, 0x4E, 0xFF, 0xFF, 0xFF};		
	broad_or_p2p = can_fr >> 16 & 0xFF;
	if (broad_or_p2p >= 240) 
	{ 	// широковещательный заголовок 
		broad (); 
		// индефикатор разлаживаем на биты
		id_bit (can_fr);
		// данные разлаживаем на биты 
	        data_bit (can_data);	
		// декодер DEC широковещательного индефикатора
		decode_broad (can_fr); 
		data_dec (can_data);
	}  
	else 
	{  
		// адресный заголовок
		p2p (); 
		// индефикатор разлаживаем на биты
		id_bit (can_fr); 
		// данные разлаживаем на биты
		data_bit (can_data); 
		// декодер адресного индефикатора 
		decode_p2p (can_fr);
	        data_dec (can_data);	
	}
	
	return 0;
} 

