# Визуальный парсер j1939 ID

Короткая консольная утилита на языке С для быстрого разбора 29-битных индефикаторов CAN-шины по стандарту j1939. Делает одну задачу, но делает её хорошо.

**Утилита в стадии разработки** 

## Что умеет утилита

- Трёх уровневая визуализация разметки ID.
- Адресный формат.
- Широковещательный формат.
- ID разлаживат на биты.
- Цветной и информативный вывод в консоль.

<details>
<summary><b>Смотреть заголовок</b></summary> 

<img width="1889" height="487" alt="Снимок экрана от 2026-05-29 17-29-42" src="https://github.com/user-attachments/assets/cafef850-59d3-4384-b2c6-c4390cc1de92" />

<img width="1899" height="492" alt="Снимок экрана от 2026-05-30 16-24-03" src="https://github.com/user-attachments/assets/8ebb25d0-96fc-40cd-a870-617a35c5c909" />


</details>

**Остановился на этом заголовке** 

<details>
<summary><b>Смотреть</b></summary>

<img width="1512" height="286" alt="Снимок экрана от 2026-06-03 12-25-21" src="https://github.com/user-attachments/assets/cccce9a7-c836-432e-a527-233970d367fd" />


</details>

<details>
<summary><b>Описание к заголовку</b></summary>

**0 байт** Приоритет, резерв, номер страницы. Приоритет суть светофор, чем меньше число тем ярче зелёный цвет. **0 -** самый высший приоритет. Моё мнение логичнее присвоить этому байту 0. 

**1 байт** Голова старший байт PGN. Клиент серверная архитектура. Только здесь немного по другому. Голова кричит остальные подчиняются. Определяет структуру. Указывает отправляется ли пакет конкретному адресу или транслируется всем. По той же логике **первый, главный**. 

**2 байт** Хвост младший байт PGN. Подчиняется. Если **голова <240** то здесь пишется адрес назначения. Если **голова >=240** расширение группы параметров.

**3 байт** Адрес источника. Физический адрес узла, который атправил это сообщение.

</details>

<details>
<summary>v0.0: viz_id_j1939.c</summary>

```c 


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
	printf (YOT"0x%x  %d\n\n"RES, var_id, var_id);
<img width="1512" height="286" alt="Снимок экрана от 2026-06-03 12-25-21" src="https://github.com/user-attachments/assets/56796625-280c-4c94-bca3-462db6a88275" />
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

```
</details>

<details>
<summary>v1.0: viz_id_j1939.c</summary>

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

```

</details> 

<details>
<summary><b>Смотреть как работает v1.0</b></summary>

<img width="1663" height="374" alt="Снимок экрана от 2026-06-03 22-03-30" src="https://github.com/user-attachments/assets/d908df6b-ce26-43e4-8d15-48d4f6ac5f42" />


</summary>
 
## В разработке

- **ID кадра** Определять автоматически 
- **byte 1 >= 240** Широковещательная рассылка
- **byte 1 < 240** Адресная рассылка
- **Если byte >= 240** По 3 байту определить какой блок (ABS, EBS, ECAS, ICE, AI)
- **1-2 byte** Определяем PGN (номер группы параметров)
- **0 byte** Приоритет, резерв, номер страницы 
- **byte < 240** По 2 байту определить адрес назначения 
- **Добавить** Данные фрейма 
