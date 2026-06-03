# bit-viz 

Что будет уметь утилита:

- [ ] Принимать выражение hex, dec, oct
- [ ] Работать в двух режимах со знаком(int32_t) без знака(uint32_t) 
- [ ] Обрабатывать 6 ключевых оператора (`<<`, `>>`, `&`, `|`, `^`, `~`)
- [ ] Побитовое разложение числа
- [ ] Цветной вывод 0-белый 1-цветная

## Запуск как работает на Планшете в Termux / Код С самый первый v0.0


<details>
<summary>v0.0: viz_bits.c</summary> 

```c

#include <stdio.h>
#include <stdint.h>
#define YOT "\033[1;33m"                                                                                               #define SIN "\033[1;34m"
#define RES "\033[0m"
// функция разлажить на биты var1 var2
int bits_var (int var_v)
{
        for (int i = 31; i >= 0; i --)
        {
                int bit = (var_v >> i) & 1;
                if (bit == 1) { printf(YOT" 1"RES); }
                else { printf(" 0"); }
        }                                                                                                                      printf("\n");
        return 0;
}
// функция разложить на биты res
int bits_res (int var_r)
{
        for (int i = 31; i >= 0; i --)
        {
                int bit = (var_r >> i) & 1;
                if (bit == 1) { printf(SIN" 1"RES); }
                else { printf(" 0"); }
        }
        printf("\n");
        return 0;
}

int main ()
{
        uint32_t var1 = 0, var2 = 0, res = 0;
        char op;
        // защита от неверного символа
        if (scanf("%i %c %i", &var1, &op, &var2) != 3) return 1;
        // вызов функции разлаживаем переменные на биты
        bits_var (var1); bits_var (var2);
        // блок операторов
        switch (op)
        {
                case '&': res = var1 & var2; break;
                case '|': res = var1 | var2; break;
                case '^': res = var1 ^ var2; break;
                // пользовательский ввод < или > по факту сдвиг << >>
                case '<': res = var1 << var2; break;
                case '>': res = var1 >> var2; break;
        }
printf( "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        // разлаживаем на биты res
        bits_res (res);
        return 0;
}


```
</details> 

    
<details>
<summary><b>Смотреть как работает<b></summary>                                                    
<img width="1200" height="1920" alt="335" src="https://github.com/user-attachments/assets/49874f71-afc8-4c6f-a7b8-7cc5e3c4191a" />


</details> 


<details>
<summary>v1.0: viz_bits.c</summary>

```c


#include <stdio.h>
#include <stdint.h>
#define YOT "\033[1;33m"
#define SIN "\033[1;34m"
#define GRIN "\033[1;32m"
#define RES "\033[0m"
// функция разлажить на биты var1 var2
int bits_var (int var_v)
{
	for (int i = 31; i >= 0; i --)
	{
		int bit = (var_v >> i) & 1;
		if (bit == 1) { printf(SIN" 1"RES); } 
		else { printf(" 0"); }
		if (i % 8 == 0) { printf(GRIN" |"RES); }
	}
	printf(SIN" %d\n"RES, var_v);
	return 0;
}
// функция разложить на биты res
int bits_res (int var_r)
{
	for (int i = 31; i >= 0; i --)
	{
		int bit = (var_r >> i) & 1;
		if (bit == 1) { printf(SIN" 1"RES); }
		else { printf(" 0"); }
		if (i % 8 == 0) { printf(GRIN" |"RES); }
	}
	printf(SIN" %d\n"RES, var_r);
	return 0;
} 
			
int main ()
{
	uint32_t var1 = 0, var2 = 0, res = 0;
	char op;
	// защита от неверного символа
	while (1)
	{
	if (scanf("%i %c %i", &var1, &op, &var2) != 3) return 1;
	// отступ от ввода 
	printf("\n");
	printf(GRIN"      byte 4     |      byte 3     |      byte 2     |      byte 1     |\n"RES);
	// вызов функции разлаживаем переменную var1 на биты
	bits_var (var1); 
	// выводим оператор 
	printf(GRIN"%74c\n"RES, op);
	// вызов функции разлаживаем переменную var2 на биты
	bits_var (var2);
	// блок операторов
	switch (op)
	{
		case '&': res = var1 & var2; break;
		case '|': res = var1 | var2; break;
		case '^': res = var1 ^ var2; break;
		// пользовательский ввод < или > по факту сдвиг << >>
		case '<': res = var1 << var2; break;
		case '>': res = var1 >> var2; break;
	}
printf( "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
	// разлаживаем на биты res 
	bits_res (res);
	printf(YOT"31            24 | 23           16 | 15            8 | 7             0 | bit\n"RES);
	printf("\n");
	} 
	return 0;
}



```


</details>


<details>
<summary><b>Смотреть как работает<b></summary>

<img width="1200" height="1920" alt="336" src="https://github.com/user-attachments/assets/f682e32d-0b38-493b-9883-866929e20175" />


</details>

