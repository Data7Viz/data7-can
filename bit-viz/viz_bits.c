#include <stdio.h>
#include <stdint.h>
#define YOT "\033[1;33m"
#define SIN "\033[1;34m"
#define RES "\033[0m"
// функция разлажить на биты var1 var2
int bits_var (int var_v)
{
	for (int i = 31; i >= 0; i --)
	{
		int bit = (var_v >> i) & 1;
		if (bit == 1) { printf(YOT" 1"RES); } 
		else { printf(" 0"); } 
	}
	printf("\n");
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






