# Анализ ID J1939

Попытка внедрить Fibonacci Factorial Euclid для анализа ID J1939. Проект на стадии разрабоки.

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

### Писал в termux 

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



</details> 
