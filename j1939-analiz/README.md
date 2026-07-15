# Карта ID J1939 на стадии разработки 


**Утилита вывводит карту индификатора CAN J1939 для быстрого анализа сети** 
**Логи это тоже сеть**

## Структура ID

- Читаем байты с лево на право начало отсчёта от нуля
- 0 > байт приоритетный
- 1 > байт голова
- 2 > байт хвост
- 3 > байт адресный

---

## Функционал

- меняя сдвиги и маски инструмен способен вытянуть любые данные
- для детального анализа разрабатываю утилиту viz_j1939.c перейти в [директорию viz-j1939](../viz-j1939/) 
- возможно расширение функционала 


--- 


## Автоматическое определение всех блоков в сети и колличество сообщений


```text

BL       0          FR        11132
блок    ДВС   все сообщения   11132 

``` 

## Адресные сообщения  (общение между блоками)


```text

P              D             H     BL             FR
приоритет   десятичная     хекс   блок   колличество сообщений
6            54528         D500    FC              1 
     
C блока FC на блок 00 было отправлено 1 адресное сообщение 

```

## Вещательные сообщения (для всех)


```text

P      D       H      BL     FR
6    65114    FE5A    2F     359  

Блок 2F с приоритетом 6 отправил 359 широковещательных сообщений номер группы параметров FE5A

```

## Проприетарные заводские свободные

логика такая же как и у вещательных

Утилита разбита на 3 блока мы как бы сжали базу данных, и можем видеть общую карту сети. 

---

## Удачная ошибка 

У меня появилось две утилиты. Допустил ошибку в условии if (sscanf ......); предупреджений от компилятора не было потом заметил исправил. После исправления программа стала работать по другому. Так появилось две прогрммы. Программа с синтатической ошибкой тоже имеет право на жизнь. 

- map_id_j1939_nosime.c 
- map_id_j1939.c 

<details>
<summary><b>Смотреть компиляцию в termux gcc</b></summary>



</details>

<details>
<summary><b>Смотреть компиляцию в Linux терминал gcc</b></summary.

<img width="881" height="100" alt="Снимок экрана от 2026-07-15 13-04-39" src="https://github.com/user-attachments/assets/fae23807-5bbd-4a52-972c-f028fa594e3a" />


</details> 
 
---

## map_id_j1939_nosime.c 


<details>
<summary><b>Эволюция карты Смотреть</b></summary>

<img width="1902" height="957" alt="Снимок экрана от 2026-06-29 15-58-04" src="https://github.com/user-attachments/assets/520d9a6d-d271-4130-b0cb-5498fd4d62f2" />


<img width="1888" height="1071" alt="Снимок экрана от 2026-07-03 11-39-55" src="https://github.com/user-attachments/assets/995eddd6-a2ff-48a1-a9c7-11606ef98ef0" />


<img width="1870" height="755" alt="Снимок экрана от 2026-07-08 18-09-56" src="https://github.com/user-attachments/assets/b80f1b76-1cc6-4100-a0fe-9ac8dfd14efa" />


<img width="1833" height="1035" alt="Снимок экрана от 2026-07-09 16-05-49" src="https://github.com/user-attachments/assets/d0544f66-a472-4877-a528-3be1bde88f40" />


<img width="1796" height="1052" alt="Снимок экрана от 2026-07-11 12-19-15" src="https://github.com/user-attachments/assets/42d674e7-3d29-4cc6-a356-a46ad639adb4" />


<img width="1779" height="1054" alt="Снимок экрана от 2026-07-15 11-28-09" src="https://github.com/user-attachments/assets/8f2383ab-fda5-42a0-b90a-2fae6fd3d0f8" />


</details>




</details> 

<details>
<summary><b>Код утилиты map_id_j1939_nosemi.c последняя версия</b></summary>

```c


#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[0;32m"
#define SIN "\033[0;34m"
#define GOT "\033[0;33m"
#define RED "\033[0;31m"
#define RES "\033[0m"

void print (char *cvet, char *stroka)
{
	printf ("%s%s---------------------------------------------------------------------------------------------------------------------------------------------\n"RES,cvet,stroka);
} 
// функция для анализа 0,1,2,3 байта 
void fyn_for_byt1_byt2_byt3 (uint32_t *arr, char *stroka2)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf (SIN" %-2X"RES" "GRIN"%-3u"RES" %s "GRIN"%-12u"RES, i, i, stroka2, arr [i]);
			a ++; if (a % 8 == 0) printf ("\n"); } 
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
				printf (SIN" %-2X"RES" >> "SIN" %-2X "RES"сбщ %-7u", i, j, su_dt [i] [j]); 
				c ++; if (c % 8 == 0) printf ("\n");
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
	
	print (GOT, "байт 1 -------------------------------------"); fyn_for_byt1_byt2_byt3 (arr_byte1, "сбщ");
	printf ("\n\n");

	print (GOT, "байт 2 -------------------------------------"); fyn_for_byt1_byt2_byt3 (arr_byte2, "сбщ");
	printf ("\n\n");

	print (GOT, "Байт 3 все адреса источники ----------------"); fyn_for_byt1_byt2_byt3 (arr_byte3, "сбщ");
	printf ("\n\n");

	print (GOT, "Байт 2 все адреса назначения ---------------"); fyn_for_byt1_byt2_byt3 (arr_dist, "сбщ");
        printf ("\n\n"); 	

	print (GOT, "Адресные с блока на >> блок байт2 << байт3 -"); fyn_su_dt (arr_sour_dist);
	printf ("\n\n");

	print (GOT, "Адресные байт1 байт2 -----------------------"); fyn_pgn (arr_prior, arr_pgn, 0, 61439);
	printf ("\n\n");
	
	print (GOT, "Вещательные байт1 байт2 --------------------");  fyn_pgn (arr_prior, arr_pgn, 61440, 65279);
	printf ("\n\n");

	print (GOT, "Заводские ----------------------------------"); fyn_pgn (arr_prior, arr_pgn, 65280, 65535);
	printf ("\n");
	 
	
	// КОЛЛИЧЕСТВО прочитаных фреймов
	kol_poter_frame = all_frame - read_frame;
	printf (GOT"Всего %-15u Прочитано %-15u Пропущено %-15u\n"RES, all_frame, read_frame, kol_poter_frame);
	printf ("\n");
	return 0;
} 	


```

</details>


---


## map_id_j1939.c 

<details>
<summary><b>Код map_id_j1939.c</b></summary>


```c


#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[0;32m"
#define SIN "\033[1;34m"
#define GOL "\033[0;33m"
#define RES "\033[0m"
void print (char *cvet, char *stroka)
{
	printf ("%s%-30s============================================================================================================================================================%s\n", cvet, stroka, RES);
} 
// функция для анализа или 0 или 1 или 2 или 3 байта 
void fyn_for_byt1_byt2_byt3 (uint32_t *arr)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf ("%-2X  сооб >  %-12u", i, arr [i]);
			a ++; if (a % 8 == 0) printf ("\n"); } 
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
				printf ("%-2X -> %-2X сооб > %-8u", i, j, arr [i] [j]);
				b ++; if (b % 8 == 0) printf ("\n");
			}
		}
	} 
} 	


// PGN параметрические диагностические 
void fyn_pgn (uint32_t *arr_p, uint32_t *arr_prior, uint32_t min, uint32_t max)
{
	int c = 0;
	for (int i = min; i <= max; i ++) 
	{  
		if (arr_p [i] > 0)
		{	
				printf ("p %-2u %-5u   %-4X ->  %-8u", arr_prior [i], i, i, arr_p [i]); 
				c ++; if (c % 6 == 0) printf ("\n"); 
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
	uint32_t arr_tcp_data [256] [256] = {0}, arr_tcp_connect [256] [256] = {0}, arr_prior [65536] = {0}, arr_pgn [65536] = {0}, arr_sour_dist [256] [256] = {0};
	uint32_t arr_byte1 [256] = {0}, arr_byte2 [256] = {0}, arr_byte3 [256] = {0}, arr_dist [256] = {0};
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;
	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы
		// парсим очищвем логи
		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file, " (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10);
		{
		read_frame ++;
		byte0 = (id >> 24) & 0xff; byte1 = (id >> 16) & 0xff; byte2 = (id >> 8) & 0xff; byte3 = id & 0xff, pgn = (id >> 8) & 0xffff, prior = (id >> 26) & 7;  
		arr_byte1 [byte1] ++;
		arr_byte2 [byte2] ++;
		arr_byte3 [byte3] ++; 
		// сообщение с блока на блок
		if (byte1 < 240) { arr_dist [byte2] ++; arr_sour_dist [byte3] [byte2] ++; arr_pgn [pgn] ++; arr_prior [pgn] = prior; }  

		else { arr_pgn [pgn] ++; arr_prior [pgn] = prior; }
		} 
    		
	} 
	fclose (file);
	
	print (SIN, "byte1 ========================="); fyn_for_byt1_byt2_byt3 (arr_byte1);
	printf ("\n\n");

	print (GRIN, "byte2 ========================"); fyn_for_byt1_byt2_byt3 (arr_byte2);
	printf ("\n\n");
	
	print (SIN, "byte3 все  блоки   источники =="); fyn_for_byt1_byt2_byt3 (arr_byte3);
	printf ("\n\n"); 

	print (GRIN, "byte2 все  блоки  назначения ="); fyn_for_byt1_byt2_byt3 (arr_dist);
	printf ("\n\n");
	
        print (SIN, "Сообщения с блока >> на блок =="); fyn_sour_dist (arr_sour_dist);
	printf ("\n\n");
	
	print (GRIN, "Адресные           сообщения ="); fyn_pgn (arr_pgn, arr_prior, 0, 61439);
	printf ("\n\n");	
	
        print (SIN, "Вещательные   сообщение  PGN =="); fyn_pgn (arr_pgn, arr_prior, 61440, 65535);
	printf ("\n\n");

	print (GRIN, "Диагностическое    сообщение ="); fyn_pgn (arr_pgn, arr_prior, 65226, 65237);
	printf ("\n");
	
	// КОЛЛИЧЕСТВО прочитаных фрейьов
	kol_poter_frame = all_frame - read_frame;
	printf (GOL"Всего %-15u Прочитано %-15u Пропущено %-15u\n"RES, all_frame, read_frame, kol_poter_frame);
	printf ("\n");
	return 0;
} 	

```

</details>


 Что выводит map_id_j1939.c и map_id_j1939_nosemi 

<details>
<summary><b>Смотреть</b></summary>

<img width="1779" height="1054" alt="Снимок экрана от 2026-07-15 11-28-09" src="https://github.com/user-attachments/assets/2f4446c3-128c-46ab-b1d1-c62a44b45d11" />

<img width="1801" height="945" alt="Снимок экрана от 2026-07-15 12-27-44" src="https://github.com/user-attachments/assets/3180149f-d7af-4fbc-a95c-8810d69aa4d7" />



</details> 
