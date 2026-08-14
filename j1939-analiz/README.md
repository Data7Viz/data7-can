# J1939 ID Map (Under Development) / Карта ID J1939 на стадии разработки

🌐 [Read in English](#-english-version) | 🇷🇺 [Читать на русском](#-русская-версия)

---

## 🌐 English Version

This utility outputs a J1939 identifier map for quick network analysis. Logs are networks too.

### 📊 ID Structure
* We read bytes from left to right, starting from index zero.
* `0` -> priority byte
* `1` -> header byte
* `2` -> tail byte
* `3` -> address byte

### ⚙️ Features
* Changing shifts and masks makes the tool capable of extracting any type of data.
* For detailed analysis, I am developing the `viz_j1939` utility; you can switch to it in the [viz-j1939 directory](../viz-j1939/).
* Future feature expansion is possible.

### 💡 A Fortunate Mistake
I ended up with two separate utilities. I made a mistake in an `if (sscanf...)` condition; there were no compiler warnings, but I noticed and fixed it later. After fixing it, the program started working differently. That is how two separate programs were born. A program with a syntax error also has a right to exist.
* `map_id_j1939_nosime.c`
* `map_id_j1939.c`

### 📱 Termux
<details>
  <summary>Show Termux compilation using gcc</summary>
  
<img width="1200" height="1920" alt="545" src="https://github.com/user-attachments/assets/412c8ed5-05b8-4f19-8316-31d003bfd4cf" />

  ```bash
  gcc map_id_j1939.c -o map_id_j1939
  ```
</details>

<details>
  <summary>Show Linux terminal compilation using gcc</summary>

<img width="881" height="100" alt="Снимок экрана от 2026-07-15 13-04-39" src="https://github.com/user-attachments/assets/fae23807-5bbd-4a52-972c-f028fa594e3a" />
  
  ```bash
  gcc map_id_j1939.c -o map_id_j1939
  ```
</details>

#### Running the map in Termux on a tablet:
I changed the number of columns to 4 and decreased `i--`. This fits my vertical and horizontal view comfortably. Tested on an 11-inch tablet.
<details>
  <summary>Show how it works</summary>
  
<img width="1200" height="1920" alt="546" src="https://github.com/user-attachments/assets/3d17dc64-d43b-4677-b079-a9ef47344005" />

<img width="1920" height="1200" alt="547" src="https://github.com/user-attachments/assets/f05fadd3-12c0-4f7b-bd1d-ebbc2ad22b5f" />

</details>

### 📄 map_id_j1939_nosime.c
<details>
  <summary>Show map evolution</summary>
  
<img width="1902" height="957" alt="Снимок экрана от 2026-06-29 15-58-04" src="https://github.com/user-attachments/assets/520d9a6d-d271-4130-b0cb-5498fd4d62f2" />


<img width="1888" height="1071" alt="Снимок экрана от 2026-07-03 11-39-55" src="https://github.com/user-attachments/assets/995eddd6-a2ff-48a1-a9c7-11606ef98ef0" />


<img width="1870" height="755" alt="Снимок экрана от 2026-07-08 18-09-56" src="https://github.com/user-attachments/assets/b80f1b76-1cc6-4100-a0fe-9ac8dfd14efa" />


<img width="1833" height="1035" alt="Снимок экрана от 2026-07-09 16-05-49" src="https://github.com/user-attachments/assets/d0544f66-a472-4877-a528-3be1bde88f40" />


<img width="1796" height="1052" alt="Снимок экрана от 2026-07-11 12-19-15" src="https://github.com/user-attachments/assets/42d674e7-3d29-4cc6-a356-a46ad639adb4" />


<img width="1779" height="1054" alt="Снимок экрана от 2026-07-15 11-28-09" src="https://github.com/user-attachments/assets/8f2383ab-fda5-42a0-b90a-2fae6fd3d0f8" />


<img width="1745" height="955" alt="Снимок экрана от 2026-07-20 17-03-10" src="https://github.com/user-attachments/assets/62a1c31d-c264-413a-8e5d-76c190bdce47" />

<img width="1699" height="1089" alt="Снимок экрана от 2026-08-09 11-23-49" src="https://github.com/user-attachments/assets/04e6ab3d-fcf0-42e7-8c04-3bf3fbeaa960" />
  
</details>



#### Output details for map_id_j1939.c and map_id_j1939_nosime.c:
<details>
  <summary>Show output</summary>
  
  
<img width="1779" height="1054" alt="Снимок экрана от 2026-07-15 11-28-09" src="https://github.com/user-attachments/assets/2f4446c3-128c-46ab-b1d1-c62a44b45d11" />

<img width="1801" height="945" alt="Снимок экрана от 2026-07-15 12-27-44" src="https://github.com/user-attachments/assets/3180149f-d7af-4fbc-a95c-8810d69aa4d7" />

</details>

---

## 🇷🇺 Русская Версия


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

## Удачная ошибка 

У меня появилось две утилиты. Допустил ошибку в условии if (sscanf ......); предупреджений от компилятора не было потом заметил исправил. После исправления программа стала работать по другому. Так появилось две прогрммы. Программа с синтатической ошибкой тоже имеет право на жизнь. 

- map_id_j1939_nosime.c программа без ошибки
- map_id_j1939.c программа с ошибкой

--- 

## Termux

<details>
<summary><b>Смотреть компиляцию в termux gcc</b></summary>

<img width="1200" height="1920" alt="545" src="https://github.com/user-attachments/assets/412c8ed5-05b8-4f19-8316-31d003bfd4cf" />


</details>

<details>
<summary><b>Смотреть компиляцию в Linux терминал gcc</b></summary> 

<img width="881" height="100" alt="Снимок экрана от 2026-07-15 13-04-39" src="https://github.com/user-attachments/assets/fae23807-5bbd-4a52-972c-f028fa594e3a" />


</details> 
 

**Запуск карты в Termux на планшете**  

Изменил колличество столбцов на 4, уменьшил (----). Для меня и по вертикали и по горизонтали комфортно. Планшет 11 дюймов. 

<details>
<summary><b>Смотреть как работает</b></summary>

<img width="1200" height="1920" alt="546" src="https://github.com/user-attachments/assets/3d17dc64-d43b-4677-b079-a9ef47344005" />

<img width="1920" height="1200" alt="547" src="https://github.com/user-attachments/assets/f05fadd3-12c0-4f7b-bd1d-ebbc2ad22b5f" />


</details> 

---

## map_id_j1939_nosime.c 

**Программа без ошибки** 


<details>
<summary><b>Эволюция карты Смотреть</b></summary>

<img width="1902" height="957" alt="Снимок экрана от 2026-06-29 15-58-04" src="https://github.com/user-attachments/assets/520d9a6d-d271-4130-b0cb-5498fd4d62f2" />


<img width="1888" height="1071" alt="Снимок экрана от 2026-07-03 11-39-55" src="https://github.com/user-attachments/assets/995eddd6-a2ff-48a1-a9c7-11606ef98ef0" />


<img width="1870" height="755" alt="Снимок экрана от 2026-07-08 18-09-56" src="https://github.com/user-attachments/assets/b80f1b76-1cc6-4100-a0fe-9ac8dfd14efa" />


<img width="1833" height="1035" alt="Снимок экрана от 2026-07-09 16-05-49" src="https://github.com/user-attachments/assets/d0544f66-a472-4877-a528-3be1bde88f40" />


<img width="1796" height="1052" alt="Снимок экрана от 2026-07-11 12-19-15" src="https://github.com/user-attachments/assets/42d674e7-3d29-4cc6-a356-a46ad639adb4" />


<img width="1779" height="1054" alt="Снимок экрана от 2026-07-15 11-28-09" src="https://github.com/user-attachments/assets/8f2383ab-fda5-42a0-b90a-2fae6fd3d0f8" />


<img width="1745" height="955" alt="Снимок экрана от 2026-07-20 17-03-10" src="https://github.com/user-attachments/assets/62a1c31d-c264-413a-8e5d-76c190bdce47" />

<img width="1679" height="1088" alt="Снимок экрана от 2026-07-22 17-58-39" src="https://github.com/user-attachments/assets/22ef9eba-3568-4fec-ab7a-9c0577ac3209" />

<img width="1699" height="1089" alt="Снимок экрана от 2026-08-09 11-23-49" src="https://github.com/user-attachments/assets/be44fe8c-9c47-4f23-ab56-b74b50895960" />


</details>

--- 

## map_id_j1939.c <- здесь синтатическая ошибка 

**Программа с ошибкой**

```c
if ( sscanf (....) == 10); 

```

## Что выводит map_id_j1939.c и map_id_j1939_nosemi 

<details>
<summary><b>Смотреть</b></summary>

<img width="1540" height="882" alt="Снимок экрана от 2026-07-28 11-51-28" src="https://github.com/user-attachments/assets/dfe6d2a0-0e1d-42ff-b7ef-0f3da054da7f" />

<img width="1679" height="1088" alt="Снимок экрана от 2026-07-22 17-58-39" src="https://github.com/user-attachments/assets/183f9ada-027d-4500-9394-e4f40f148ce3" />



</details> 

---

## map_id_j1939_file_obd.c 

**Программа для чтения с файла и с OBD в реальном времени** 

- Изменил логику на входе утилиты

```c 
    
    FILE *file;
	if (argc >= 2) 
	{ file = fopen (argv [1], "r");
	if (file == NULL) { printf (" Ошибка : не удалось открыть файл %s\n", argv [1]); return 1; }
	}
	else { file = stdin; }

``` 
- Можно читать с файла
- можно читать с OBD2 разъёма в реальном времени 
- Удалил заголовки полей и "|".
- Добавил библиотеку (unistd.h) читаем с файла для имитации реального времени ( sleep(0.5) )


```c 

while ()
{.......
sleep (0.5) 
}

```
- Вызов функций для вывода на печать положил в цикл (while). 
- Если закоментировать можно вывести на печать одну функцию.

<details>
<summary><b>Смотреть как работает с файла</b></summary> 

https://github.com/user-attachments/assets/19803f27-e49c-486c-9bb7-54da0d69a638

</details> 

### Читаем в  реальном времени 

На выключеном зажигании подключаем и запускаем CANable на Linux. 
Включаем зажигание смотрим как запускается система.

Посмотреть [Демонстрацию работы в реальном времени (Видео ВКонтакте)](https://vk.ru/clip-227479791_456239043?c=1)

--- 

## map_time_j1939.c 

**Разработка и анализ сообщений J1939 во времени** 

<details>
<summary><b>Фото1 ./map_time_j1939</b></summary> 

<img width="1471" height="493" alt="Снимок экрана от 2026-08-07 20-02-23" src="https://github.com/user-attachments/assets/76b1c0da-f116-42be-a3cc-2432c6a16f53" />


</details> 

Если выполнить математическую операцию >>  Длительность лога - Дельта PGN =  Время молчания блока. 

---

<details>
<summary><b>Фото2 ./map_time_j1939</b></summary>

<img width="1648" height="499" alt="Снимок экрана от 2026-08-07 21-15-45" src="https://github.com/user-attachments/assets/e4711384-ffb3-43cb-8e6a-8e4a25747b5c" />


</details>

Запрограммировал время молчания , простой блока. Это суммарное время, в течении которого прибор не вещал сообщения.  

--- 

<details>
<summary><b>Фото3 ./map_time_j1939</b></summary>
	
<img width="1583" height="562" alt="Снимок экрана от 2026-08-08 11-15-47" src="https://github.com/user-attachments/assets/143fb854-58e5-4b26-92d0-1c14225b1013" />

</details> 

- То как сообщения лежат в сети по краям.  зазор на старте | напрмер массив 256 сообщений | зазор на финише. 
- Сумарный зазор КРАЯ = (Зазор на финише - Зазор на старте) - Длительность лога.  
- dlittej_log - (pgn_end [pgn] - pgn_start [pgn]). 
- Суммарный зазор по идее будет равен периоду вещания. 

---

<details>
<summary><b>Фото4 ./map_time_j1939</b></summary>
	
<img width="1785" height="1142" alt="Снимок экрана от 2026-08-08 17-22-55" src="https://github.com/user-attachments/assets/e7ff71c0-759e-4e83-bc79-b3b62a76c66a" />

</details>

Переписал код. Пытаюсь поймать закономерность. 

--- 

<details>
<summary><b>Фото5 ./map_time_j1939</b></summary>
<img width="1789" height="1106" alt="Снимок экрана от 2026-08-09 09-33-12" src="https://github.com/user-attachments/assets/1cb48f70-6146-45cf-8562-a1eb00978ac4" />

</details>

Пытаюсь вывести на печать в поле вещательных зазор по краям. Сейчас общая картина чем ближе число к длительности лога тем меньше краевые зазоры. Нужен детальный анализ по краям. 
- pgn_end [pgn] - pgn_start [pgn] видим FEFF сбщ 2 края 10.002 сек <- это зазор с левого края (фото 5)
- dlitel_log (pgn_end [pgn] - pgn_start [pgn]) видим FEFF сбщ 2 15.756 сек <- это зазор и с левого и правого края общий зазор (фото 3) 
- Получается первое сообщение на 10 сек второе на 20 сек левый зазор 10 сек + правый зазор 5 сек = 15 сек
- FEF8 сбщ 25 края 24.028 сек <- здесь уже толком ни чего не понятно. При вычитании ты видишь общюю сумму по краям. (фото3) 

--- 

<details>
<summary><b>Фото6 map_time_j1939</b></summary> 
<img width="1699" height="1089" alt="Снимок экрана от 2026-08-09 11-23-49" src="https://github.com/user-attachments/assets/8c320b98-ca62-4ce8-9116-2570ac93b52a" />

</details>

Запрограммировал зазоры с левой и с правой стороны.

- П - приоритет 
- Б - блок источник
- С - колличество сообщений
- ЛВ - зазор с левой стороны
- ПР - зазор в правой стороны

./map_time_j1939 это общая картина сети.

### Техническая деталь структура ID J1939

<details>
<summary><b>Фото7 ./viz_j1939 это микроскоп</b></summary>
<img width="1793" height="604" alt="Снимок экрана от 2026-08-04 12-52-36" src="https://github.com/user-attachments/assets/8a9e554b-f65e-437c-a4d5-0922e0351bde" />

</details>

0xFECA этот PGN блоки тормозной системы, ДВС, АКПП, пневмоподвеска делят между собой. 

**-п 6 FECA 65226 б 11 с 101 лв 0.638 пр 0.117 <- здесь "каша"** 

Существуют ли подобные PGN которые блоки делят между собой? Требуется дальнейшее исследование. 

---
---

### Итоги разработки карты ID CAN J1939 на 9.08.2026 год map_id_j1939

Именна переменных + комментарии к коду ??? 

<details>
<summary><b>Смотреть код программы map_id_j1939.c</b></summary> 

```c

#include <stdio.h>
#include <stdint.h>
#define GRIN "\033[0;32m"
#define SIN "\033[0;34m"
#define GOT "\033[0;33m"
#define GR "\033[0;90m"
#define RES "\033[0m"

void print (char *cvet, char *stroka)
{
	printf ("%s%s---------------------------------------------------------------------------------------------------\n\n"RES,cvet,stroka);
} 
// функция для анализа 0,1,2,3 байта 
void fyn_for_byt1_byt2_byt3 (uint32_t *arr, char *str)
{
	int a = 0;
	for (int i = 0; i <= 255; i ++)
	{
		if (arr [i] > 0) { printf (""GR" |"RES" %s"SIN" %-2X"RES" "GRIN"%-3u"RES" сбщ %-7u", str, i, i, arr [i]);
			a ++; if (a % 6 == 0) printf ("\n"); } 
	}
} 

// функция вещательные сообщения 
void fyn_pgn (uint32_t *arr_prior, uint32_t *arr_pgn, uint32_t *pgn_sour, double *pgn_start, double *pgn_end, double start_time, double end_time, uint32_t min, uint32_t max)
{
	int b = 0;
	for (int i = min; i <= max; i ++) 
	{ 
			if (arr_pgn [i] > 0)  
			{	
				double zaz_lv = pgn_start [i] - start_time;
				double zaz_pr = end_time - pgn_end [i]; 
				printf (""GR" |"RES""GRIN" п "RES"%u"SIN" %4X"RES" %-5u "GRIN" б "RES"%-3u "GRIN"с "RES"%-7u "GRIN"лв "RES"%-6.3lf "GRIN"пр "RES"%-6.3lf", arr_prior [i], i, i, pgn_sour [i], arr_pgn [i], zaz_lv, zaz_pr); 
				b ++; if (b % 3 == 0) printf ("\n"); 
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
				printf (""GR" |"RES" ис"SIN" %-2X"RES" наз"SIN" %-2X "RES" сбщ %-7u", i, j, su_dt [i] [j]); 
				c ++; if (c % 6 == 0) printf ("\n");
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
	uint32_t pgn_sour [65536] = {0}, arr_byte1 [256] = {0}, arr_byte2 [256] = {0}, arr_byte3 [256] = {0}, arr_br_byte3 [256] = {0}, arr_pgn [65536] = {0}, arr_prior [65536] = {0}, arr_sour_dist [256] [256] = {0}; 
	uint32_t byte0 = 0, byte1 = 0, byte2 = 0, byte3 = 0, pgn = 0, prior = 0;	
	// счётчики вещательных и адресных сообщений общее колличество
	uint32_t count_br = 0, count_addr = 0;
	// длительность снятия лога 
	double start_time = 0.0, end_time = 0.0;
	// переменные для тайминга
	double pgn_start [65536] = {0.0}, pgn_end [65536] = {0.0};

	while (fgets (byf_file, sizeof (byf_file), file))
	{
		all_frame ++; // все фреймы
		// парсим очищвем логи
		for (int i = 0; i <= 7; i ++) data [i] = 0;
		if (sscanf (byf_file," (%lf) %*s %x [%*d] %hx %hx %hx %hx %hx %hx %hx %hx", &time,&id,&data[0],&data[1],&data[2],&data[3],&data[4],&data[5],&data[6],&data[7]) == 10)
		{
		end_time = time;
		read_frame ++;
		byte0 = (id >> 24) & 0xff; byte1 = (id >> 16) & 0xff; byte2 = (id >> 8) & 0xff; byte3 = id & 0xff, pgn = (id >> 8) & 0xffff, prior = (id >> 26) & 7;  
		
		if (read_frame == 1) { start_time = time; }  
		
		// все блоки сети
		arr_byte3 [byte3] ++; 
		// адресные
		if (byte1 < 240) { 
			arr_prior [pgn] = prior; arr_byte1 [byte1] ++; arr_sour_dist [byte3] [byte2] ++; count_addr ++;}  	

		// вещательное
		else { 
			arr_prior [pgn] = prior; 
			arr_br_byte3 [byte3] ++; 
			arr_pgn [pgn] ++;
		        pgn_sour [pgn] = byte3;	
			count_br ++;}
			
		if (pgn_start [pgn] == 0.0 || time < pgn_start [pgn]) pgn_start [pgn] = time;



		if (pgn_end [pgn] == 0.0 || time > pgn_end [pgn]) pgn_end [pgn] = time; 


		} 
		else { printf ("Не прочитаные : %s", byf_file); } 
	} 
	fclose (file);
	kol_poter_frame = all_frame - read_frame;
	double dlitel_log = end_time - start_time; 
	
	printf ("\n");
	print (GOT, "[ Байт 1 ] Сетевые / Транспортные ---------------------------------"); fyn_for_byt1_byt2_byt3 (arr_byte1, "byte 1");
	printf ("\n\n");

	print (GOT, "[ Байт 2 ] Блоки источники вещательных сообщений [ байт 1 >= 240 ] "); fyn_for_byt1_byt2_byt3 (arr_br_byte3, "бл ист");
        printf	 ("\n\n");

	print (GOT, "[ Байт 3 ] Все блоки источники ------------------------------------"); fyn_for_byt1_byt2_byt3 (arr_byte3, "бл ист");
        printf ("\n\n"); 	

	print (GOT, "[ Байт 2 Байт 3 ] Сообщение с блока на блок [ byte 1 < 240 ] ------"); fyn_su_dt (arr_sour_dist);
	printf ("\n\n");

	//print (GOT, "[ байт 2 Байт 3 ] Адресные сообщения [ byte 1 < 240 ] -------------"); fyn_pgn (arr_prior, arr_pgn, 0, 61439);
	//printf ("\n\n");
	
	print (GOT, "[ Байт 1 Байт 2] Вещательные сообщения [ byte 1 >= 240 ] ----------"); fyn_pgn (arr_prior, arr_pgn, pgn_sour, pgn_start, pgn_end, start_time, end_time, 61440, 65279);
	printf ("\n\n");

	print (GOT, "[ Байт 1 Байт 2 ] Заводские Проприетарные [ byte 1 >= 240 ] -------"); fyn_pgn (arr_prior, arr_pgn, pgn_sour, pgn_start, pgn_end, start_time, end_time, 65280, 65535);
	printf ("\n\n");
	
	printf (GRIN"Всего %-7u Прочитано %-7u Пропущено %-7u"RES" "GOT" Длительность лога %-7lf сек"RES, all_frame, read_frame, kol_poter_frame, dlitel_log);
	printf (SIN"\tВещательных %-7u  Адресных %-7u\n"RES, count_br, count_addr);
	return 0;
} 	

```

</details>

<details>
<summary><b>Смотреть как работает ./map_id_j1939</b></summary>
<img width="1699" height="1089" alt="Снимок экрана от 2026-08-09 11-23-49" src="https://github.com/user-attachments/assets/061ed0ec-206b-4061-a153-fb5ea0252f5b" />

</summary> 
<img width="4096" height="1430" alt="752" src="https://github.com/user-attachments/assets/a04c53aa-f0cb-4abe-9587-60b13431a629" />

</details> 

---
---

## Разработка программы time_j1939 для анализа времени лог с файла

Часы, минуты, секунды это время для человека. Чтоб понять что происходит под "капотом" CAN J1939 нужно опуститься ниже на низкий уровень. Миллисекунды - Микросекунды. 
Написал логику перемещения по времени. Можно проанализировать любой промежуток времени. Какие были события за 1,2,05 сек. и так далее любое время. Выбор времени задаётся в исходном коде. 

<details>
<summary><b>Фрагмент кода для перемещения по времени</b></summary>

```c
if (read_frame == 1)
                {
                        start_time = time;
                        frame_0 = ceil (start_time); // обнуляю разряды после точки стартового сообщения
                        frame_jmp = frame_0 + 1; // прыгаю на 1 секунду вперё
                        printf ("%lf  %lf\n", frame_0, frame_jmp);
                }

```

</details>

<img width="1079" height="74" alt="Снимок экрана от 2026-08-14 11-24-17" src="https://github.com/user-attachments/assets/810301a1-7dcd-450b-8dc3-45660a99a979" />

---

## Анализ всех событий в течении секунды 

- time С 1782249169.000000 ДО 1782249170.000000 
- сообщений за 1 секунду 888
- загрузка сети 44% 
- загрузка % = колличество кадров * время передачи одного кадра ( 888 * 0ю000500 = 0ю444000 ) 
- при скорости 250 кб/с длительность кадра 500 мкс. 
- при скорости 500 кб/с время передачи кадра 250 мкс. 

<details>
<summary><b>Фрагмент кода для просмотра событий в течении 1 сек</b></summary>

```c

if (read_frame == 1)
                {
                        start_time = time;
                        frame_0 = ceil (start_time); // обнуляю разряды после точки стартового сообщения
                        frame_jmp = frame_0 + 1; // прыгаю на 1 секунду вперё
                }
                if ((time >= frame_0) && (time <= frame_jmp))
                {
                        printf ("%-20lf", time);
                        count_0_jmp ++; // счётчик сообщений 
                        if (count_0_jmp % 13 == 0) printf ("\n"); // отрисовка таблицы  

                }

```

</details> 

<details>
<summary><b>Смотреть все события за 1 секунду></b></summary>
	
<img width="1855" height="1093" alt="Снимок экрана от 2026-08-14 12-24-37" src="https://github.com/user-attachments/assets/a74a1cb2-d464-4d3b-bae3-109f1e2633b1" />

</details> 

---

## Межфреймовый зазор (интервал) Пространство между кадрами

**Зазор это или**

- Тишина сети ( ни один блок не вещал )
- Задержка ( Арбитраж )

<details>
<summary><b>Фрагмент кода для просмотра зазора</b></summary>

```c

if (read_frame == 1)
                {
                        start_time = time;
                        frame_0 = ceil (start_time); // обнуляю разряды после точки стартового сообщения
                        frame_jmp = frame_0 + 1; // прыгаю на 1 секунду вперё
                }
                if ((time >= frame_0) && (time <= frame_jmp))
                {
                        if (prochl_time > 0.0)
                        {
                                zazor = time - prochl_time; // вычисляем зазор между кадрами 
                                printf ("%-10lf", zazor);
                                count_0_jmp ++; // счётчик сообщений 
                                if (count_0_jmp % 20 == 0) printf ("\n"); // отрисовка таблицы  
                        }
                        prochl_time = time; // берём прошлое время 
                }

```

</details> 

<details>
<summary><b>Смотреть зазор между кадрами</b></summary> 
												
<img width="1829" height="870" alt="Снимок экрана от 2026-08-14 13-37-03" src="https://github.com/user-attachments/assets/c065b662-7665-42fd-9042-595aee0c9c1d" />

</details>

**продолжаю развивать тему межфреймового зазора** 

Добавил ID. Между какими индефикаторами находится это пространство. 

<details>
<summary><b>Смотреть что получилось</b></summary>

</summary> 
