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




```

</details>


<details>
<summary><b>Смотреть как работает что выводит</b></summary>

<img width="1883" height="1096" alt="Снимок экрана от 2026-06-27 08-51-44" src="https://github.com/user-attachments/assets/55331a61-1123-473b-9cd9-a78f34640782" />


</details>  

--- 

<details>
<summary></b>Какие блоки в сети колличество сообщений с каждого блока всего сообщений прочитаные и потеряные сообщения</b></summary> 

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



</details> 
