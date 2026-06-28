# Песочница 

Черновые наброски и эксперименты 

## Файлы 
- **filter.c** - поисковик, фильтрация, дубликаты
- **reader.c** - парсер текстовой строки лога 
- **reader_filter.c** - совмещение чтение файлов  поиск, анализ, фильтр 

## Утилита для строго парсинга CAN-логов

Легковесный консольный инструмент на языке С для разбора сырых логов. 

**Идея** Архитектура ядра позволяеть менять логику **на лету** сдвиги (>>) маски (0xFFF) логические элементы (& | ~ ^) условие (if (sscanf ..... == >=) и так далее....
)
## Ядро для утилиты разбора логов

---

<details>
<summary><b>Какие блоки в сети</b></summary>

```c

#include <stdio.h>
int main ()
{ 
	int data [] = {1,4,4,3,9,7,7,6,6,6,8,10,11,4,13,12,11,13,11,14,14,5,18,18,18,34,45,11,1,5,7,8};
	int buf [256] = {0};
	int var = 0;
	int razm = sizeof (data) / sizeof(data[0]);
	for (int i = 0; i < razm; i ++)
	{
		var = data [i];
		if (buf [var] == 0)
		{
			buf [var] ++;
			printf ("%d\n", var);
		}
	}
	return 0;
} 

```
</details> 

---

<details>
<summary><b>Колличество сообщений с каждого блока</b></summary> 

```c


#include <stdio.h>
int main ()
{ 
	int data [] = {1,4,0,0,0,4,3,9,7,7,6,6,6,8,10,11,4,13,12,11,13,11,14,14,5,18,18,18,34,45,11,1,5,7,8};
	int buf [256] = {0};
	int var = 0;
	int razm = sizeof (data) / sizeof(data[0]);
	for (int i = 0; i < razm; i ++)
	{
		var = data [i];
		buf [var] ++;
	}
	for (int j = 0; j < 256; j ++)
	{
		if (buf [j] > 0) 
		printf (" %d %d\n", j, buf [j]);
	} 
	return 0;
} 


``` 

</details> 

--- 

<details>
<summary><b>Читаем строку лога CAN</b></summary>

```c 


#include <stdio.h>
#include <stdint.h>
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
	uint8_t data [8] = {0}; 

	fgets (buf_file, sizeof (buf_file), file);

	sscanf (buf_file, " %lf%x%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx", &time,&id,&data [0],&data [1],&data [2],&data [3],&data [4],&data [5],&data [6],&data [7]);
      
	printf (" %lf %x", time, id);
	for (int i = 0; i < 8; i ++)
	{
		printf (" %x", data [i]);
	} 
	printf ("\n");
	fclose (file);
	return 0;
} 	


``` 

</details> 

---

<details>
<summary><b>Первая утилита для разбор лога</b></summary>

```c


#include <stdio.h>
#include <stdint.h>
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
	uint32_t buf_analize [65535] = {0};
	uint32_t kol_string = 0;
	uint32_t poisk = 0;
	while (fgets (buf_file, sizeof (buf_file), file))
	{
		kol_string ++;
		sscanf (buf_file, " (%lf) %*s %x %*[hhd] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]);
        		        
		poisk = id & 0xff;
		buf_analize [poisk] ++; 
	} 
	fclose (file);
	
	printf ("\n");
	for (int i = 0; i < 65535; i ++)
	{
		if (buf_analize [i] > 0)
		{
			printf (" номер блока %d   \t  отправленно сообщений %u\n", i, buf_analize [i]);
		}
	}
	printf ("\n");
	printf (" Всего сообщений %u\n\n", kol_string);	
	return 0;
} 	




</details>


<details>
<summary><b>Смотреть как работает что выводит</b></summary>

<img width="1883" height="1096" alt="Снимок экрана от 2026-06-27 08-51-44" src="https://github.com/user-attachments/assets/55331a61-1123-473b-9cd9-a78f34640782" />


</details>  

--- 

<details>
<summary><b>Какие блоки в сети колличество сообщений с каждого блока всего сообщений прочитаные и потеряные сообщения</b></summary> 

```c


#include <stdio.h>
#include <stdint.h>
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
	uint32_t buf_analize [65536] = {0};
	uint32_t all_string = 0;
	uint32_t poisk = 0;
	uint32_t read_string = 0;
	uint32_t kol_poter_string = 0;
	while (fgets (buf_file, sizeof (buf_file), file))
	{
		all_string ++;
		if (sscanf (buf_file, " (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10);
		{
         	poisk = id & 0xff;
		buf_analize [poisk] ++;
	        read_string ++;	
		} 
	} 
	fclose (file);
	
	printf ("\n");
	for (int i = 0; i <= 65535; i ++)
	{
		
		if (buf_analize [i] > 0)
		{
			printf (" номер блока %X   \t  отправленно сообщений %u\n", i, buf_analize [i]);

		}
	}
	printf ("\n");
	kol_poter_string = all_string - read_string;
	printf (" Всего сообщений \t %u\n", all_string);
	printf (" Прочитаные сообщения \t %u\n", read_string);	
	printf (" Пропущенно  сообщений \t %u\n", kol_poter_string);
	return 0;
} 	




```

</details>


<details>
<summary><b>Что выводит утилита</b></summary> 

<img width="1803" height="1095" alt="Снимок экрана от 2026-06-27 11-26-10" src="https://github.com/user-attachments/assets/ada0dc05-a404-40f9-9f01-d47b249b7bac" />


</details> 

---

<details>
<summary><b>Карта ID CAN J1939 (утилоита)</b></summary>

```c


#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[0;32m"
#define SIN "\033[0;34m"
#define GOL "\033[0;33m"
#define RES "\033[0m"
void cikl1 (uint32_t *arr)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf ("Блок %-2X сообщений %-12u", i, arr [i]);
			a ++; if (a % 6 == 0) printf ("\n"); } 
	}
} 

void cikl2 (uint32_t *arr, uint32_t a, uint32_t b)
{
	int d = 0;
	for (int i = 0; i <= 65535; i ++) 
	{ 
		if (arr [i] > 0)
		{	
			if (i >= a &&  i <= b)
			{
				printf (" pgn %-2X  %-2d  -> %-10u", i, i, arr [i]); 
				d ++; if (d % 6 == 0) printf ("\n");
			} 
		} 
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
		
	char byf_file [256] = {0}; 
	double time = 0.0;
	uint32_t id = 0;
	uint16_t data [8] = {0};
	uint32_t mas_byte3 [256] = {0};

	uint32_t all_frame = 0; // все фреймы 
	uint32_t byte3 = 0; // переменная для адресного 3 байт ID 
	uint32_t read_frame = 0; // прочитаные фрейьы
	uint32_t kol_poter_frame = 0; // потеряные фреймы 
	// переменные для 1 байта
	uint32_t mas_byte1_p2p [256] = {0};
	uint32_t mas_byte1_br [256] = {0};
	uint16_t byte1 = 0;
	uint32_t p2p = 0;
	uint32_t brodcas = 0;
	// PGN
	uint32_t mas_byte1_2 [65536] = {0};
	uint32_t byte1_2 = 0;
	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы

		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file, " (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10);
		{
		// анализируем 3 адресный байт ID какие блоки в сети колличество сообщений с каждого блока
         	byte3 = id & 0xff; 
		mas_byte3 [byte3] ++;
	        read_frame ++;	// прочитаные фреймы 
		} 
		// анализируем 1 байт ID вещательный или адресный колличество вещат и адрес сообщений 
		byte1 = (id >> 16) & 0xff;
		if (byte1 < 240) { mas_byte1_p2p [byte1] ++; p2p ++; }
		
		if (byte1 >= 240) { mas_byte1_br [byte1] ++; brodcas ++; } 
		// PGN
		byte1_2 = (id >> 8) & 0xffff;
		if (byte1_2 >= 61440) { mas_byte1_2 [byte1_2] ++; } 
	        	
	} 
	fclose (file);
	
	printf ("\n");
	
	// все блоки в сети и колличество сообщений с каждого блока
	printf (GRIN"================================================================================ Все сообщения =================================================================================\n"RES); 
	cikl1 (mas_byte3); // вызов функции 

        kol_poter_frame = all_frame - read_frame; // вычисляем колличество не прочитаных сообщений

	printf ("\n"); 	
	printf (GRIN"\t\t\tВсего сообщений  %-15u"RES, all_frame);
	printf (GRIN"\tПрочитано сообщений  %-15u"RES, read_frame);
	printf (GRIN"\tПропущенно сообщений  %-15u\n\n"RES, kol_poter_frame);
	
	// все адресные сообщения и колличество сообщений с каждого блока
	printf (SIN"============================================================================ Адресныe сообщений =================================================================================\n"RES);
	cikl1 (mas_byte1_p2p);
	printf ("\n");	
	printf (SIN"\t\t\t\t\t\t\t\t\t\tВсего Сообщений %u\n\n"RES, p2p);
	
	// все вещательные сообщения и колличество сообщений с каждого блока
	printf (GOL"====================================================================== Широковещательные сообщения ==============================================================================\n"RES); 
	cikl1 (mas_byte1_br);	
	printf ("\n");
	printf (GOL"\t\t\t\t\t\t\t\t\t\tВсего Сообщений %u\n\n"RES, brodcas);
	
	// PGN параметрические
	printf (GRIN"======================================================================== Параметрические =======================================================================================\n"RES);
	cikl2 (mas_byte1_2, 61440, 65087);
	printf ("\n\n");
	
	// PGN диагностические 
	printf (SIN"======================================================================== Диагностические ========================================================================================\n"RES);
	cikl2 (mas_byte1_2, 65088, 65279); 
	printf ("\n\n");
	
	// PGN свободные 
	printf (GOL"======================================================================= Свободные ===============================================================================================\n"RES);
	cikl2 (mas_byte1_2, 65280, 65535); 
	printf ("\n\n");
	
	return 0;
} 	

```

</details>


<details>
<summary><b>Смотреть как работает</b></summary>

<img width="1893" height="939" alt="Снимок экрана от 2026-06-28 11-33-44" src="https://github.com/user-attachments/assets/1ad6ce73-df02-4a72-a7e6-496a451526b0" />


</details> 

---
