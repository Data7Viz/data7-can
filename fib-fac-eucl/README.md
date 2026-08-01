# Анализ ID J1939 

# ЕСТЬ БЕЗУМНАЯ ИДЕЯ

Попытка внедрить Fibonacci Factorial Euclid + Neuron для анализа ID J1939. Проект на стадии разрабоки.

**Результат за ранее не известен** 

Перенёс с директории tests:

- fibonacci.c
- factorial.c 
- euclid.c 

---

## Fibonacci 

Наложить структуру ID на Fibonacci

<details>
<summary><b>Эволюция разработки в скринах</b></summary> 

<img width="571" height="640" alt="Снимок экрана от 2026-07-28 14-03-28" src="https://github.com/user-attachments/assets/744b7661-6cb8-4fbe-a07d-b102175ec755" />

<img width="385" height="1108" alt="Снимок экрана от 2026-07-28 17-37-47" src="https://github.com/user-attachments/assets/c55559e6-915d-4fbc-926b-dbf7dc6cc94a" />

<img width="323" height="658" alt="Снимок экрана от 2026-07-28 17-42-36" src="https://github.com/user-attachments/assets/7697d716-f54d-4c2c-99e9-811d4945504e" />

<img width="394" height="639" alt="Снимок экрана от 2026-07-28 17-56-29" src="https://github.com/user-attachments/assets/0a43617a-8284-4793-9154-8f3c9c546c25" />

<img width="427" height="648" alt="Снимок экрана от 2026-07-28 17-59-49" src="https://github.com/user-attachments/assets/2ff02e9b-7a9b-4ca1-8493-3f2284540669" />

<img width="515" height="651" alt="Снимок экрана от 2026-07-28 18-55-51" src="https://github.com/user-attachments/assets/28283043-a46e-4f3b-bebc-068ce474140c" />

</details>

---

### История и моя философия 

Обратимся к первоисточнику. История позволяет заглянуть под капот. Пара кроликов. Вывел второй слой я его назвал пара Фибоначчи. Все подробности будут в статье на Хабр. После публикации опубликую ссылку. 

Число **1  1  2  3   5   8**

Пара  **2  2  4  6  10  16**  

**Математическая реальность**

Из математики 0 не удалишь он там есть был и будет. Он в коде программы.

**Физическая реальность**

В начале была одна пара. Поэтому я ноль не выводил. 

<details>
<summary><b>Смотреть скрин</b></summary>
  
<img width="684" height="630" alt="Снимок экрана от 2026-07-28 20-05-05" src="https://github.com/user-attachments/assets/3b9a03ab-113f-4583-a79e-0a313ed3f409" />

</details> 

---

### Termux 

Добавил два поля деления. Написал шапку заголовок. 

<details>
<summary><b>Смотреть код</b></summary>

```c


#include <stdio.h>
#define GRIN "\033[0;32m"
#define RES "\033[0m"
void print ()
{
	printf (GRIN"\t     bit | ряд    число  |  пара     |  del    | del \n"RES);
} 
int main ()
{
	double a = 0, b = 1, res = 0, del = 0, to_fib = 0, del1 = 0; 
	unsigned int count = 28, id = 0x0CF00400, bit = 0;
	print (); 
	for (int i = 1; i <= 29; i ++)
	{
		res = a + b;
		del = b / a; 
		del1 = a / b;
		b = a; 
		a = res;
		to_fib = res * 2;
		bit = (id >> count) & 1;	
		printf ("\t %-2u   %u "GRIN" | "RES" %-3u   %-6.0lf"GRIN" | "RES"  %-7.0lf "GRIN"|"RES" %-7.4lf "GRIN"|"RES" %-4.4lf\n", count, bit, i, res, to_fib, del, del1);
		count --;
		if (i == 3 || i == 5 || i == 13 || i == 21)
		{ 
			printf ("\n");
		} 
	} 
	printf (GRIN"\t\t\t\t%X\n"RES, id); 
	return 0;
} 

``` 

</details>


<details>
<summary><b>Смотреть как работает</b></summary>

<img width="1200" height="1920" alt="670" src="https://github.com/user-attachments/assets/a8d3feed-7d1f-4c6a-8233-907157c148e7" />


</details>

- только на 12-м ряду стабилизируется .618.
- 4 ряд интересен по своему с одной стороны 0.5 с другой 2 после приоритета.

---

### Termux 

Наложил структуру ID J1939 на последовательность Fibonacci по новому.

<details>
<summary><b>Смотреть: хэш Фибоначчи</b></summary>

<img width="1200" height="1920" alt="692" src="https://github.com/user-attachments/assets/7cdb3adb-0d9f-46dc-b523-3ac5a3dcbdda" />


</details>

<details>
<summary><b>Смотреть Код</b></summary>

```c


#include <stdio.h>
#define GRIN "\033[0;32m"
#define RES "\033[0m"
void print ()
{
	printf (GRIN"\t     bit | ряд    число  |  хэш fib \n"RES);
} 
int main ()
{
	unsigned int a = 0, b = 1, res = 0, fib = 0, byf_fib = 0; 
	unsigned int count = 28, id = 0, bit = 0;
	scanf (" %i", &id);
	print (); 
	for (int i = 1; i <= 29; i ++)
	{
		res = a + b;
		b = a; 
		a = res;
		bit = (id >> count) & 1;
		fib = bit * res;
		byf_fib += fib;
		printf ("\t %6u "GRIN" | "RES" %-3u   %-6.0u"GRIN" | "RES" %-5u\n", bit, i, res, fib);
		count --;
		if (i == 3 || i == 5 || i == 13 || i == 21)
		{ 
			printf ("\n");
		} 
	} 
	printf (GRIN"ID J1939 0x%X  %20u\n"RES, id, byf_fib); 
	 
	return 0;
} 

```

</details> 

---

## Факториал

<details>
<summary><b>Смотреть fibonacci -> factorial</b></summary> 


</details>

### Факториал:

- Нет 0 и быть не может
- Взрывной рост 
- Возможный Хаос
- Беспорядок
- 0 аварийный стоп 
- 0 тот кто может остановить 

### Фибоначчи: 

- Растёт медленее
- Здесь уже порядок
- Заполнение пространства

<details>
<summary><b>fib_fact.c</b></summary>

```c

#include <stdio.h>
int main ()
{
	unsigned int fib_a = 0, fib_b = 1, fib_res = 0, fact = 1;
	for (int i = 1; i <= 10; i ++)
	{
		fib_res = fib_a + fib_b;
		fib_b = fib_a; 
		fib_a = fib_res;
		fact *= i;
		printf ("\tряд %-3u Число Фибоначчи = %-15u  n!  %-3u = %u\n", i, fib_res, i, fact);
	} 
	return 0;
} 


```

</details> 


















