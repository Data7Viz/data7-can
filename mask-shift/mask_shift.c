#include <stdio.h>
#include <stdint.h>
#define S "\033[1;34m"
#define Y "\033[1;33m" 
#define G "\033[1;32m"
#define R "\033[0m"
int bit_f (uint64_t var_f, uint8_t razr_f)
{
	for (int i = razr_f; i >= 0; i--)
	{
		int bit = (var_f >> i) & 1;
		if (bit ==1) { printf(S"1"R); }
		else { printf("0"); }
		if (i % 8 == 0) { printf(G"|"R); } 
	}
	printf ("\n");
	return 0;
}

int main ()
{
uint64_t var = 0, res = 0, res1 = 0, mask = 0; 
uint16_t shift = 0;
uint16_t razr = 0;
char op1, op2;
printf (" Выбери Разрядность начало от нуля (7, 15, 31, 63)  : ");
if (scanf("%hu", &razr) == 1) 
while(scanf("%li %c %hu %c %li", &var, &op1, &shift, &op2, &mask) == 5) 
{
printf("\n");
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
	printf(Y" %c "R, op2);
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
printf (S"%20lu    0x%lx\n"R, res1, res1);
printf ("\n");
} 
}

 
