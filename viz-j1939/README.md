# Визуальный парсер CAN j1939

**Консольная утилита на языке С для разбора сырых данных CAN-шины по стандарту j1939.**

## Утилита на стадии разработки

- **ID кадра** Определять автоматически
- **byte 1 >= 240** Широковещательная рассылка
- **byte 1 < 240** Адресная рассылка
- **Если byte >= 240** По 3 байту определить какой блок (ABS, EBS, ECAS, ICE, AI)
- **1-2 byte** Определяем PGN (номер группы параметров)
- **0 byte** Приоритет, резерв, номер страницы
- **byte < 240** По 2 байту определить адрес назначения

- **Параметрический** с  - 0xF000 - 61440
- **Параметрический** до - 0xFE3F - 65087

- **Диагностический** с  - 0xFE40 - 65088
- **Диагностический** до - 0xFEFF - 65279                       

- **Резерв**          с  -  0xFF00 - 65280
- **Резевр**          до -  0xFFFF - 65535

---

## Заголовок 

<details>
<summary><b>Эволюция заголовка</b></summary> 

<img width="1889" height="487" alt="Снимок экрана от 2026-05-29 17-29-42" src="https://github.com/user-attachments/assets/cafef850-59d3-4384-b2c6-c4390cc1de92" />

<img width="1899" height="492" alt="Снимок экрана от 2026-05-30 16-24-03" src="https://github.com/user-attachments/assets/8ebb25d0-96fc-40cd-a870-617a35c5c909" />

<img width="1512" height="286" alt="Снимок экрана от 2026-06-03 12-25-21" src="https://github.com/user-attachments/assets/cccce9a7-c836-432e-a527-233970d367fd" />

<img width="1896" height="322" alt="Снимок экрана от 2026-06-04 19-30-07" src="https://github.com/user-attachments/assets/d022f676-e423-4ddf-a494-a7fea8508fa9" />

<img width="1903" height="343" alt="Снимок экрана от 2026-06-05 12-47-29" src="https://github.com/user-attachments/assets/05bf89f9-15ba-4060-8188-d4d3d1e7d642" />

<img width="1900" height="287" alt="Снимок экрана от 2026-06-18 15-47-45" src="https://github.com/user-attachments/assets/c294584c-baa6-4ac5-bbee-48464d6763d9" />


</details>

<details>
<summary><b>Описание к заголовку</b></summary>

**0 байт** Приоритет, резерв, номер страницы. Приоритет суть светофор, чем меньше число тем ярче зелёный цвет. **0 -** самый высший приоритет. Моё мнение логичнее присвоить этому байту 0. 

**1 байт** Голова старший байт PGN. Клиент серверная архитектура. Только здесь немного по другому. Голова кричит остальные подчиняются. Определяет структуру. Указывает отправляется ли пакет конкретному адресу или транслируется всем. По той же логике **первый, главный**. 

**2 байт** Хвост младший байт PGN. Подчиняется. Если **голова <240** то здесь пишется адрес назначения. Если **голова >=240** расширение группы параметров.

**3 байт** Адрес источника. Физический адрес узла, который атправил это сообщение.

**1-2 байт** Вычислить назначение \ параметрическое \ дтагностическое \ частное. 

</details>

---

<details>
<summary><b>Текущая версия viz_j1939.c</b></summary>

```c



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
	printf (GRI" |       time           |   Pr | R Pg|      PF        PGN     PS         |    Src Addr     | "RES);
	printf (GRI" |   d1   |   d2     |    d3    |    d4    |    d5    |    d6    |    d7    |    d8    | \n"RES);	
	return 0;
} 
// адресный заголовок (шапка)
int p2p ()
{
	printf (GRI" |       time           |   Pr | R Pg|      PF        p2p    Dst Adr     |   Src Addr      | "RES);
	printf (GRI" |  d1    |   d2     |    d3    |    d4    |    d5    |    d6    |    d7    |    d8    | \n"RES);
	return 0;
} 

// время фрейма
int time (double var_time)
{
	printf (SIN"  %lf"RES, var_time);
	return 0;
} 

// разлаживаем ID на биты
int id_bit (uint32_t var_id)
{
	printf ("\t\t\t");
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
		printf (SIN"%11x"RES, var_dec [i]);
		
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
	printf (SIN"     %4u %5u %1u %7s %13u %24u"RES, byte0, bitR, bitP, type, byte1_2, byte3);
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
	printf (SIN"     %4u %5u %1u %11u %16u %17u"RES, byte0, bitR, bitP, byte1, byte2, byte3);
	return 0;
} 

int main ()
{
	uint32_t can_fr = 0, broad_or_p2p = 0;
	double time_frem = 1718715372.123456;
	can_fr = 0x0cf00400; 
	uint8_t can_data [8] = {0xFF, 0x7D, 0xB4, 0x23, 0x4E, 0xFF, 0xFF, 0xFF};		
	broad_or_p2p = can_fr >> 16 & 0xFF;
	if (broad_or_p2p >= 240) 
	{ 	// широковещательный заголовок 
		broad ();  
		// индефикатор разлаживаем на биты
		id_bit (can_fr);
		// данные разлаживаем на биты 
	        data_bit (can_data);
		// время фрейма
		time (time_frem);	
		// декодер DEC широковещательного индефикатора
		decode_broad (can_fr); 
		// dec данных 
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
		// время фрейма
		time (time_frem);
		// декодер адресного индефикатора 
		decode_p2p (can_fr);
	        // dec данных  
		data_dec (can_data);	
	}
	
	return 0;
} 


```

</details> 

<details>
<summary><b>Смотреть как работает</b></summary>

<img width="1900" height="287" alt="Снимок экрана от 2026-06-18 15-47-45" src="https://github.com/user-attachments/assets/3c7a624a-f65d-4107-8acc-789b02535757" />



</summary>
 
 
