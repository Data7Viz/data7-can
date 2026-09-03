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

---

## Структура лога CAN J1939

- Время (time)
- Индификатор (ID)
- Данные (data) 

---

# ID ID ID   

```text

 |  BYTE 0   |  BYTE 1        |   BYTE 2       |  BYTE 3
 |IDIDID|IDID|IDIDIDIDIDIDIDID|IDIDIDIDIDIDIDID|IDIDIDIDIDIDIDID 
 |ПРИОРИТЕТ  |  ГОЛОВА        |   ХВОСТ        |  АДРЕСНЫЙ

``` 

## MAP_ID_J1939

**Утилита вывводит карту индификатора CAN J1939 для быстрого анализа сети** 
**Логи это тоже сеть**

### Структура ID

- Читаем байты с лево на право начало отсчёта от нуля
- 0 > байт приоритетный
- 1 > байт голова
- 2 > байт хвост
- 3 > байт адресный
- если byte_1 >= 240 byte_1 +  byte_2 склеиваем и получаем PGN byte_3 адрес источника
- если byte_1 < 240 byte_3 адрес источника byte_2 адрес назначения byte_1 функции ( команды, запрос - ответ, транспортировка ) 
- byte_0 2,3,4 биты приоритет чем меньше число тем ярче зелёный цвет
- byte_0  0 и 1 бит расширение 
- индефикатор 29 битный

### Функционал

- меняя сдвиги и маски инструмен способен вытянуть любые данные
- для детального анализа разрабатываю утилиту viz_j1939.c перейти в [директорию viz-j1939](../viz-j1939/) 
- возможно расширение функционала 

### Удачная ошибка 

У меня появилось две утилиты. Допустил ошибку в условии if (sscanf ......); предупреджений от компилятора [gcc] на ноутбуке не было потом заметил исправил. Компилятор в Termux предупреждение выдал. После исправления программа стала работать по другому. Так появилось две прогрммы. 

- map_id_j1939_nosime.c - программа без ошибки
- map_id_j1939_semi.c - программа с ошибкой

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

## map_id_j1939.c 


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

<img width="1046" height="1032" alt="Снимок экрана от 2026-08-14 20-59-21" src="https://github.com/user-attachments/assets/cd0c6494-2b0f-4633-901e-3bf60eaeaedc" />


</details>

--- 

### map_id_j1939_semi.c

**Программа с ошибкой**

```c
if ( sscanf (....) == 10); 

```

### Что выводит map_id_j1939_semi.c и map_id_j1939_nosemi 

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

### Читаем в реальном времени

На выключеном зажигании подключаем и запускаем CANable на Linux. 
Включаем зажигание смотрим как запускается система.

Посмотреть [Демонстрацию работы в реальном времени (Видео ВКонтакте)](https://vk.ru/clip-227479791_456239043?c=1)

---
--- 

# TIME TIME TIME 

```text

1782249169. |     991       |     480
            | МИКРОСЕКУНДЫ  | МИЛЛИСЕКУНДЫ

```

### Структура времени CAN J1939

- Микросекунды
- Миллисекунды  

Часы, минуты, секунды это время для человека. Чтоб понять что происходит под "капотом" CAN J1939 нужно опуститься на низкий уровень. Миллисекунды - Микросекунды.

### map_time_j1939.c

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

### map_id_j1939

Изучаю и анализирую время J1939 для добавления функций в карту map_id_j1939. Анализ времени только для вещательных сообщений. Адресные пока опустим это по идее событие. 
 
<details>
<summary><b>Итоги работы ./map_id_j1939</b></summary>
<img width="1699" height="1089" alt="Снимок экрана от 2026-08-09 11-23-49" src="https://github.com/user-attachments/assets/061ed0ec-206b-4061-a153-fb5ea0252f5b" />

</summary> 
<img width="4096" height="1430" alt="752" src="https://github.com/user-attachments/assets/a04c53aa-f0cb-4abe-9587-60b13431a629" />

</details> 

---
---

### time_j1939

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

### Анализ всех событий в течении секунды 

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

### Межфреймовый зазор (интервал) Пространство между кадрами

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


Добавил ID. Между какими индефикаторами находится это пространство. 

<details>
<summary><b>Смотреть что получилось</b></summary>
	
<img width="1776" height="1094" alt="Снимок экрана от 2026-08-14 15-15-29" src="https://github.com/user-attachments/assets/a3a4fc97-521d-4b29-930b-a0f5bde9938d" />

</details> 

---

### Запрограммировал период вещания 

Программа выводит только максимальное значение периода.

<details>
<summary><b>Смотреть период</b></summary>
	
<img width="1642" height="162" alt="Снимок экрана от 2026-08-14 17-15-02" src="https://github.com/user-attachments/assets/705437f7-af95-4cfa-91ab-68b64aa93b9a" />

</details> 

---

### Запрограммировал межфреймовый зазор на максимальное значение  

Программа выводит только максимальное значение 

<details>
<summary><b>Смотреть</b></summary>
<img width="1615" height="207" alt="Снимок экрана от 2026-08-14 17-51-21" src="https://github.com/user-attachments/assets/6e7e8414-7e28-457f-90ab-97f034040635" />

</details>

---
---

### Итоги работы карты  map_id_j1939 

<details>
<summary><b>Смотреть как работает</b></summary>
	
<img width="1046" height="1032" alt="Снимок экрана от 2026-08-14 20-59-21" src="https://github.com/user-attachments/assets/646b83f0-9ec4-45bf-ad6a-6b2474b73b17" />
<img width="1727" height="1108" alt="Снимок экрана от 2026-08-14 20-59-46" src="https://github.com/user-attachments/assets/7dc383c3-8679-4d67-bd29-386f9f5db779" />

</details>

**Для вещательных сообщений**

- **ПР** - приоритет
- **БЛ** - блок 
- **СБЩ** - сообщений 
- **ЗАЗ.ЛЕВ** - зазор с левой стороны (это время появления первого кадра считаем от старта лога)
- **ЗАЗ.ПР** - зазор с правой стороны (зто время последнего сообщения считаем от финиша лога) 
- **ЗАДЕРЖКА** - межкадровое пространство ( либо блок ждёт либо тишина в сети это когда ни один блок не вещает) 


<details>
<summary><b>Смотреть как рабботает</b></summary>
	
<img width="1780" height="1149" alt="Снимок экрана от 2026-08-16 14-20-33" src="https://github.com/user-attachments/assets/c7fb410e-3f4d-43b7-aae1-34ab2a46408c" />

</details>

**Для вещательных и проприетарных сообщений**

- **Пр** - приоритет
- **Ист** - блок источник  
- **Сбщ** - колличество сообщений
- **Дс.Лв** - дистанция или расстояние до первого сообщения от начала или от старта лога
- **Дс.Пр** - дистанция или расстояние от последнего сообщщения до финиша лога

**В самом низу**

- **Время передачи** - сколько сеть была занята передачей данных
- **Время тишины** - сколько шина была свободна
- **Средняяя длительность одного кадра** - Длительность одного бита при скорости 250 кбит.с  Tбит = 1 / 250 000 = 4 мкс. Тбит = 1 . 500 000 = 2 мсс 

По time идёт разработка для добавления информации в карту map_id_j1939 для общей оценки сети. В карту добавлять по идее уже ни чего не стоит. Буду развивать другой движок time_j1939. 

---
--- 

### time_j1939 Изучаю межфреймовое пространство 

<details>
<summary><b>Логика</b></summary>

```c

if (read_frame == 1)
                {
                        start_time = time;
                        frame_0 = ceil (start_time); // обнуляю разряды после точки стартового сообщения
                        frame_jmp = frame_0 + 1; // прыгаю на 1 секунду вперё
                }

                if ((time >= frame_0) && (time <= frame_jmp))
                {
                                if (byte1 >= 240)
                                {
                                if (prochl_time  > 0.0)
                                {
                                zazor = time - prochl_time; // вычисляем зазор между кадрами 
                                printf ("    "GRIN"%-18lf %-8X"RES" зазор %-10lf"SIN"%-8X %-18lf"RES, prochl_time, prochl_id, zazor, id, time);

                                count_0_jmp ++; // счётчик сообщений 

                                if (count_0_jmp % 2 == 0) printf ("\n"); // отрисовка таблицы  
                                }
                                        prochl_time = time; // берём прошлое время 
                                        prochl_id = id;
                                }


                }


```

</details>

<details>
<summary><b>Что вывела логика</b></summary>
	
<img width="1560" height="1091" alt="Снимок экрана от 2026-08-15 12-12-05" src="https://github.com/user-attachments/assets/542569d1-c5eb-48c7-8784-42d352ae14db" />

</details>

Цель кода. Увидеть между какими PGN "дырки". Я беру прошлое время и номер группы параметров и новое время и номер группы и через вычитание (zazor = time - prochl_time) смотрю временной интервал между сообщениями. Программа выводит сырой ID. Но прочитать можно пусть и не на 100 %. Данных много хотя здесь всего одна секунда. Что интересно загрузка сети 44 % что при анализе 1 сек что при анализе всего лога. Если анализировать по секундно например в цикле можно выйти на проблемный участок. 

### time_j1939 Убрал сырое время добавил номера строк читаем от 0

<details>
<summary><b>Смотреть как работает</b></summary>
	
<img width="1695" height="973" alt="Снимок экрана от 2026-08-15 17-02-25" src="https://github.com/user-attachments/assets/cc60e205-38b1-4074-93c3-f6b2504cefe9" />

</details> 

---

### time_j1939 Время тишины сети свободное пространство между кадрами

<details>
<summary><b>Смотреть как работает</b></summary> 
	
<img width="1334" height="1069" alt="Снимок экрана от 2026-08-27 18-04-21" src="https://github.com/user-attachments/assets/1a859e9c-723a-4b4e-ba2f-64561df4cfd1" />

</details>

```text

zazor = (time - prochl_time) - 0.000500;

```
Сначало вычисляем зазор (пространство) между кадрами. Потом вытичаем время трансляции одного CAN-кадра 0.000500 (500 мкс). 

- Я принял за средне время трансляции одного кадра 500 мкс. 
- Физический размер одного CAN-кадра на шине не стабильный. Он постоянно меняется от сообщения к сообщению. 

**Я бы сравнил это с адресной арифметикой**

- p_a ++; мы можем гулять по памяти.
- frame_start = time;
- frame_jmp = frame_start + 1.0; мы можем гулять по времени (можно выставить любое окно для анализа).

---

### time_j1939 Цикличность отправки PGN

Цикличность отправки PGN можно вывести и без технической документации. 
Прописываем условие и интересующий PGN. 

```с

if (pgn == 0xF000)
{
    .....
} 

```

<details>
<summary><b>Смотреть цикличность PGN 0xF000</b></summary>  
	
<img width="1321" height="201" alt="Снимок экрана от 2026-08-27 18-06-28" src="https://github.com/user-attachments/assets/7b22069e-1f5c-4b9f-bd3a-ecdcc9941af7" />

</details>

- интервал вещания 100 млс.
- блок источник 0x10 десятичное 16 это замедлитель карданной передачи
- приоритет 0x18 приоритет 6

<details>
<summary><b>Смотреть вычисление приоритета утилита mask_shift</b></summary>
<img width="962" height="205" alt="Снимок экрана от 2026-08-27 19-54-10" src="https://github.com/user-attachments/assets/a25a4c32-c21e-4ce8-a19c-0b3ba547d71a" />

</details>

Мы видим приоритет 0x18 -> 1 1 0 0 0 -> 8 + 16 + 0 + 0 + 0 = десятичное 24 
0 и 1 бит 0 байта это часть PGN расширение. Поэтому начало отсчёта приоритета со 2 бита это наш 0 бит. 1 1 0 -> 4 + 2 + 0 = 6; 
По факту приоритет 6. 

<details>
<summary><b>Смотреть цикличность PGN 0xF004 10 млс</b></summary> 
	
<img width="1337" height="1073" alt="Снимок экрана от 2026-08-27 18-07-49" src="https://github.com/user-attachments/assets/678bb5f1-4d6f-4223-bb25-6380cda2de57" />

</details>

---

### Переименновал time_j1939.c на time_j1939_manual.c.  

Посекундная ручная навигация по логу. 

Функционал time_j1939_manual

- Ручной тайм-навигатор.
- Детальный анализ выбранных временных отрезков лога CAN/J1939
- Быстрый прыжок на любую секунду лога ( аналог адресной арифметики )
- Вырезание любого окна анализа
- Парный вывод сообщений Синий предыдущее Зелёный текущее Белый межфреймовое пространство
- Вычисление межстрочных зазоров расчёт реальных пауз
- Смотри поле Время тишины Цикличность отправки PGN

<details>
<summary><b>Смотреть работу time_j1939_manual</b></summary>
	
<img width="980" height="1097" alt="Снимок экрана от 2026-08-28 15-25-27" src="https://github.com/user-attachments/assets/b71eef23-b0cc-42f1-ab4b-1018122a4ec0" />

</details> 

---
---

## Итоги map_id_j1939

Основной инструмент 

- map_id_j1939
- viz_j1939 (находится в директории viz-j1939)
- time_j1939_manual (думаю теперь и time_j1939_manual будет развиваться)

В map_id_j1939 добавил функцию интервал вещания PGN (интервал обновления). 

<details>
<summary><b>Смотреть функцию</b></summary> 
	
<img width="1896" height="1036" alt="Снимок экрана от 2026-08-30 15-10-49" src="https://github.com/user-attachments/assets/ca3db3fa-b5e2-44dc-b766-6a24b066a1e9" />

</details> 

- **Пр** приоритет
- **Ист** блок источник
- **Сбщ** колличество сообщений 
- **Инт** интевал вещания 
- **Дс.Лв** дистанция с лева когда появилось первое сообщение от старта записи. Например:
запустил запись лога, включил зажигание, можно проанализировать запуск системы. 

```text

if (первый прочитанный фрейм == 1)
Время самого первого фрейма = time;

Дс.Лв = минимальное время PGN - время свмого первого фрейма. 

```
- **Дс.Пр** дистанция с права засыпание системы. Например:
выключи зажигание  и продолжай записывать лог 10 - 30 может 60 сек. 

---

### time_j1939_manual  Изучаю время j1939 

<details>
<summary><b>Смотреть свободное пространство между кадрами</b></summary>
	
<img width="661" height="1089" alt="Снимок экрана от 2026-09-03 09-11-33" src="https://github.com/user-attachments/assets/ead9a9e2-3f0c-4999-b58f-85d81bfdeb9c" />

</details>

**PGN 0xF002** интервал вещания 10 млс.

Но с другой стороны это свободное пространсво в сети. Скорость сети 250 кб/с. Время вещания одного кадра (среднее значение) -> 500 мкс. PGN 0xF002 это маркер через каждые 10млс сеть будет занята 500 мкс таким образом в сети образовалось окно. 

```text

Свободное пространство = Интервал вещания - Время вещания 1 кадра;
       9.5 млс         =       10 млс     -    500 мкс

  |    F002    |      ОКНО      |    F002 
  | 500 мкс    |    9.5 млс     |    F002

```

**0xF002** это маркер.

От начала 0xF002 до начала следующего 0xF002 10 млс. Получается максимальное количество сообщений 20. Если в данном окне 20 сообщений значит сеть занята на 100 %. Это примеродного из возможных вариантов анализа. 

Можно например собрать логику которая будет считать количество сообщений каждую секунду. Если в секунду 2000 сообщений сеть загружена на 100%. 





