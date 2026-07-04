# Карта ID J1939

**Утилита вывводит карту индификатора CAN J1939 для быстрого анализа сети 
**Логи это тоже сеть**

## Структура ID

- Читаем байты с лево на право начало отсчёта от нуля
- 0 > байт приоритетный
- 1 > байт голова
- 2 > байт хвост
- 3 > байт адресный

## Техничка 

**DM1  [FECA]** - Активные ошибки 
**DM2  [FECB]** - Сохранёные ошибки 
**DM3  [FECC]** - Сброс ошибок
**DM4  [FECD]** - Стоп кадр
**DM5  [FECE]** - Готовность системы
**DM11 [FED3]** - Сброс щшибок

## Функционал

- меняя сдвиги и маски инструмен способен вытянуть любые данные
- возможно расширение функционала
- для детального анализа разрабатываю утилиту **viz_j1939.c** перейти в [директорию viz-j1939](../viz-j1939/) 
- автоматическое определение всех блоков в сети
- отслеживание диалогов между блоками
- транспортный протокол 
- парметрические и диагностические PGN
- раздел диагностики и сервиса
- прочитаные и пропущенные сообщения

---

<details>
<summary><b>Эволюция карты Смотреть</b></summary>

<img width="1902" height="957" alt="Снимок экрана от 2026-06-29 15-58-04" src="https://github.com/user-attachments/assets/520d9a6d-d271-4130-b0cb-5498fd4d62f2" />


<img width="1888" height="1071" alt="Снимок экрана от 2026-07-03 11-39-55" src="https://github.com/user-attachments/assets/995eddd6-a2ff-48a1-a9c7-11606ef98ef0" />


</details>


## Программу считаю законченной, надеюсь ошибок в логике нет, со временем возможно что-то изменю

**СМОТРЕТЬ ЛОГИ**

<details>
<summary><b>С отключенной массой</b></summary>

<img width="1846" height="637" alt="Снимок экрана от 2026-07-04 15-10-11" src="https://github.com/user-attachments/assets/c8aeaa9b-2a71-4e3a-84c7-ffb122b75ab7" />


</details>

<details>
<summary><b>C включенной массой и выключеным зажиганием</b></summary>

<img width="1878" height="635" alt="Снимок экрана от 2026-07-04 15-11-45" src="https://github.com/user-attachments/assets/9156d986-59a0-4a38-9f28-207ebaa05cf6" />


</details>

<details>
<summary><b>Зажигание включено</b></summary>

<img width="1889" height="960" alt="Снимок экрана от 2026-07-04 15-12-29" src="https://github.com/user-attachments/assets/1208a6a5-7156-404a-b84f-20f39a5ba1d3" />


</details>

<details>
<summary><b>Запуск ДВС</b></summary>

<img width="1885" height="965" alt="Снимок экрана от 2026-07-04 15-08-27" src="https://github.com/user-attachments/assets/72e08894-9433-451f-918c-142976e5de9c" />


</details>

<details>
<summary><b>Подключение scanmatik к ДВС</b></summary>

<img width="1872" height="943" alt="Снимок экрана от 2026-07-04 15-13-40" src="https://github.com/user-attachments/assets/4df28181-dd46-45d4-a7b1-5bb5b5f34050" />


</details> 

<details>
<summary><b>Код утилиты</b></summary>

```c


#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[1;32m"
#define SIN "\033[0;34m"
#define GOL "\033[0;33m"
#define RES "\033[0m"
void print (char *cvet)
{
	printf ("%s---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"RES, cvet);
} 
// функция для анализа 0,1,2,3 байта 
void fyn_for_byt1_byt2_byt3 (uint32_t *arr, char *stroka1, char *stroka2)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf (" %s %-2X %s %-12u", stroka1, i, stroka2, arr [i]);
			a ++; if (a % 6 == 0) printf ("\n"); } 
	}
} 
// функция адрес источника адрес назначения 
void fyn_sour_dist (uint32_t arr [256] [256])
{
	int b = 0;
	for (uint32_t i = 0; i <= 255; i ++)
	{
		for (uint32_t j = 0; j <= 255; j ++)
		{
			if (arr [i] [j] > 0)
			{
				printf (" %-2X  -> %-2X  %-12u", i, j, arr [i] [j]);
				b ++; if (b % 6 == 0) printf ("\n");
			}
		}
	} 
} 	


// PGN параметрические диагностические 
void fyn_pgn (uint32_t *arr, uint32_t *arr_prior, uint32_t min, uint32_t max)
{
	int c = 0;
	for (int i = min; i <= max; i ++) 
	{ 
		if (arr [i] > 0)
		{	
				printf ("pri  %-2u pgn %-2X  -> %-10u", arr_prior [i], i, arr [i]); 
				c ++; if (c % 6 == 0) printf ("\n"); 
		} 
	} 
} 
// TCp
void fyn_tcp (uint32_t arr [256] [256])
{
	int d = 0;
	for (uint32_t i = 0; i <= 255; i ++)
	{
		for (uint32_t j = 0; j <= 255; j ++)
		{
			if (arr [i] [j] > 0)
			{
				printf (" %-3X  ->>   %-3X     %-10u", i, j, arr [i] [j]);
				d ++; if (d % 6 == 0) printf ("\n"); 
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

	uint32_t all_frame = 0; // все фреймы 
	uint32_t read_frame = 0; // прочитаные фрейьы
	uint32_t kol_poter_frame = 0; // потеряные фреймы 
	// память для логики 
	uint32_t arr_tcp_data [256] [256] = {0}, arr_tcp_connect [256] [256] = {0}, arr_byte2 [256] = {0}, arr_byte3 [256] = {0}, arr_pgn [65536] = {0}, arr_sour_dist [256] [256] = {0};
	uint32_t arr_prior [65536] = {0}; 
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;
	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы
		// парсим очищвем логи
		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file, " (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10);
		{
		read_frame ++;
		byte0 = (id >> 24) & 0xff; byte1 = (id >> 16) & 0xff; byte2 = (id >> 8) & 0xff; byte3 = id & 0xff, pgn = (id >> 8) & 0x3ffff, prior = (id >> 26) & 7;  
		// все блоки сети 
		arr_byte3 [byte3] ++;
		// TCP
		if (byte1 == 0xEC) { arr_tcp_connect [byte3] [byte2] ++; } 
		else if (byte1 == 0xEB) { arr_tcp_data [byte3] [byte2] ++; } 
		// сообщение с блока на блок
		else if (byte1 < 240) { arr_sour_dist [byte3] [byte2] ++; arr_pgn [pgn] ++; arr_prior [pgn] = prior; }  
		// pgn
		else { arr_pgn [pgn] ++; arr_prior [pgn] = prior; }
		} 
    		
	} 
	fclose (file);
	// все блоки отправители 
	printf (SIN"\t\tВсе блоки в сети\n"RES);
	fyn_for_byt1_byt2_byt3 (arr_byte3, "блок", "фреймы");
	printf ("\n"); 
	// сообщение с блока на блок 
	print (GRIN); printf (SIN"\t\tСообщение с блока >> на блок\n"RES);
	fyn_sour_dist (arr_sour_dist);
	printf ("\n");
	// TCP	
	print (GRIN); printf (SIN"\t\tTCP Запрос на подключение\n"RES);
	fyn_tcp (arr_tcp_connect); 		
	printf ("\n");
	print (GRIN); printf (SIN"\t\tTCP ответ данные\n"RES);
	fyn_tcp (arr_tcp_data);
	printf ("\n");	
	// PGN параметрические
	print (GRIN); printf (SIN"\t\tPGN параметрические\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 61440, 65087);
	printf ("\n");
	// PGN диагностические 
	print (GRIN); printf (SIN"\t\tPGN диагностические\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 65088, 65279); 
	printf ("\n");
	// PGN свободные 
	print (GRIN); printf (SIN"\t\tPGN проприетарные\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 65280, 65535);
        printf ("\n");	
	// диагностика и сервис
	print (GRIN); printf (SIN"\t\t\t\t\t\t\t\t\t\tРАЗДЕЛ ДИАГНОСТИКИ И СЕРВИСА\n"RES);
	printf (SIN"\t\tДИАГНОСТИКА Коды неисправностей (DM1 - DM5, DM25)\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 0xFE6D, 0xFECE);
	printf ("\n");
	// сервис 
	print (GRIN); printf (SIN"\t\tСЕРВИС Паспорта блоков и калибровок (DM11, DM19, DM24)\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 0xFE6F, 0xFED8);
	printf ("\n");
 	// системные
	print (GRIN); printf (SIN"\t\tСИСТЕМНЫЕ Запросы параметров и опрос сети (Request)\n"RES);
	fyn_pgn (arr_pgn, arr_prior, 0xEA00, 0xEBFF);
	printf ("\n");
	print (GRIN); 
	// КОЛЛИЧЕСТВО прочитаных фрейьов
	kol_poter_frame = all_frame - read_frame;
	printf (GOL"Всего %-15u Прочитано %-15u Пропущено %-15u\n"RES, all_frame, read_frame, kol_poter_frame);
	printf ("\n");
	return 0;
} 	

```

</details>


---
