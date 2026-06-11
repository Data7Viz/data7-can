# Сдвиги и маски

Интерактивная консольная утилита для визуализации побитовых операций, сдвигов и наложения масок. Разработана в рамках проекта **data7-can** для наглядного анализа содержимого CAN-кадров ID DATA. Писал в termux на смартфоне. Перекинул код на планшет. 

## Возможности 

- Поддержка разрядности
- Автоматическое распознание форматов ввода: **DEC** **HEX**
- Визуальное разделение байтов символ `|`
- Цветовая подсветка единичных битов и операторов в терминале
- Выход из программы `CTRL + C` 
- Возможны доработки 

---

## Компиляция запуск Смотреь как работает в termux планшет
<details>
<summary><b>Смотреть</b></summary>

<img width="1200" height="1920" alt="365" src="https://github.com/user-attachments/assets/fe071138-ed48-41f6-9f80-395368050861" />


</details>

---

## Актуальная версия кода

<details>
<summary><b>mask_shift.c</b></summary>

```c
    

#include <stdio.h>
#include <stdint.h>

#define S "\033[1;34m"
#define Y "\033[1;33m"
#define G "\033[1;32m"
#define R "\033[0m"

int bit_f (uint64_t var_f, uint16_t razr_f)
{
	for (int i = razr_f; i >= 0; i --)
	{
		int bit = (var_f >> i) & 1;
		if (bit == 1)
		{
			printf (S"1"R);
		}
		else 
		{
			printf ("0");
		} 
		if (i % 8 == 0)
		{
			printf (G"|"R);
		}
	}
	printf ("\n");
	return 0;
} 

int main ()
{
	uint64_t var = 0, res = 0, res1 = 0, mask = 0;
	uint16_t shift = 0, razr = 0;
	char op1, op2;
	printf (" Выбери разрядность начало от нуля (7, 15, 31, 63) : ");
	if (scanf("%hu", &razr) == 1)
		while (scanf(" %li %c %hi %c %li", &var, &op1, &shift, &op2, &mask) == 5)
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
			printf (S"%20lu   0x%lx\n"R, res1, res1);
			printf ("\n");
		}
	return 0;
} 


```

</details>

 

