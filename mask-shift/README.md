# Сдвиги и маски

Интерактивная консольная утилита для визуализации побитовых операций, сдвигов и наложения масок. Разработана в рамках проекта **data7-can** для наглядного анализа содержимого CAN-кадров ID DATA. Начинал писать в **termux на смартфоне**. Потом проект перекочевал **на планшет в termux**. Теперь допиливаю на ноутбуке **Linux**.   

## Возможности 

- Поддержка разрядности
- Визуальное разделение байтов символ |
- Цветовая подсветка единичных битов и операторов в терминале

---

## Техничка 
 
Для того чтобы код работал с переменными которые могут принимать значение со знаком **Нужен**

- Тип данных **long long** вместо **unsigned long long**
- Ввод **scanf** спецификатор **%lli** считывает значение со знаком и **hex** **dec**
- Вывод **printf** **%lld** 
- Для планшета смартфона ноутбука нужно коректировать под размер экрана
- Пользовательский ввод **>** **<** по факту **>>** **<<**
- Выход из программы **Ctrl C**
---

## Компиляция и запуск 
<details>

<summary><b>Смотреть как работает смартфон termux</b></summary>

<img width="2448" height="3264" alt="379" src="https://github.com/user-attachments/assets/a3d813b9-0f97-4f0d-b489-66b3c31a7fca" />


</details>

<details> 

<summary><b>Смотреть как работает планшет termux</b></summary>

<img width="1200" height="1920" alt="365" src="https://github.com/user-attachments/assets/fe071138-ed48-41f6-9f80-395368050861" />

</details> 

<details> 

<summary><b>Смотреть как работает ноутбук</b></summary> 

<img width="1893" height="581" alt="Снимок экрана от 2026-06-11 16-07-36" src="https://github.com/user-attachments/assets/4446e91a-b027-4da2-82a4-c1d3b8362409" />


</details>

---


## Актуальная версия кода

<details>
<summary><b>mask_shift.c</b></summary>

```c
    

#include <stdio.h>

#define S "\033[1;34m"
#define Y "\033[1;33m"
#define G "\033[1;32m"
#define R "\033[0m"
int bit_f (unsigned long long var_f, unsigned short razr_f)
{
	for (int i = razr_f; i >= 0; i --)
	{
		int bit = (var_f >> i) & 1;
		if (bit == 1)
		{
			printf (S" 1"R);
		}
		else 
		{
			printf (" 0");
		} 
		if (i % 8 == 0)
		{
			printf (G" | "R);
		}
	}
	printf ("\n");
	return 0;
} 

int main ()
{
	unsigned long long var = 0, res = 0, res1 = 0, mask = 0;
	unsigned short shift = 0, razr = 0;
	char op1, op2;
	printf (" Выбери разрядность начало от нуля (7, 15, 31, 63) : ");
	if (scanf("%hu", &razr) == 1)
		while (scanf(" %llx %c %hi %c %llx", &var, &op1, &shift, &op2, &mask) == 5)
		{
			printf ("\n");
			printf ("   ");
			bit_f (var, razr);
			printf (Y" %c "R, op1);

			switch (op1)
			{

				case '>':
					res = var >> shift;
					break;
				case '<':
					res = var << shift;
					break;
			}

			bit_f (res, razr);
			printf (Y" %c "R, op2);
			bit_f (mask, razr);
			
			switch (op2)
			{
				case '&':
					res1 = res & mask;
					break;
				case '|':
					res1 = res | mask;
					break;
				case '^':
					res1 = res ^ mask;
					break;
			}

			printf (Y" = "R);
			bit_f (res1, razr);
			printf (S"%20llu   0x%llx\n"R, res1, res1);
			printf ("\n");
		}
	return 0;
} 


						



```

</details>

 

