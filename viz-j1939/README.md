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

## Вещательные делятся на следующие диапазоны 

- **Параметрический** с  - 0xF000 - 61440
- **Параметрический** до - 0xFE3F - 65087

- **Диагностический** с  - 0xFE40 - 65088
- **Диагностический** до - 0xFEFF - 65279                       

- **Резерв**          с  -  0xFF00 - 65280  ( Проприетарные \ Заводские ) 
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


```

</details> 

<details>
<summary><b>Смотреть как работает Читаем активные ошибки</b></summary>

<img width="1900" height="287" alt="Снимок экрана от 2026-06-18 15-47-45" src="https://github.com/user-attachments/assets/3c7a624a-f65d-4107-8acc-789b02535757" />



</summary>
 
 
