#include <cstdint>
#include <cstdio>

int main(int argc, char *argv[]) {
  // открываем файл
  FILE *file = fopen(argv[1], "rb");
  // берём память на стэке
  char byf[128] = {0};
  uint8_t write[128] = {0};
  uint8_t cout = 0;
  uint64_t time = 0;
  fgets(byf, sizeof(byf), file);// ложим строку на стэк 
  char *p_b = byf; // берём 0 адрес byf 
  uint8_t *p_w = write; // берём 0 адрес write
  cout = 0; // обнуляем счётчик
  
  // идём до конца строки чистим и выводим числа  
  while (*p_b != '\0') {
    if (*p_b >= '0' && *p_b <= '9') {
      *p_w = *p_b - 48; // преобразование символа в число + запись в write
      p_w++; // двигаем указатель массива write 
      cout++; // колличество прочитаных символов
    } 
    else if (*p_b >= 'A' && *p_b <= 'F') {
      *p_w = *p_b - 'A' + 10; // преобразование символа в число
      p_w++;                  // двигаем указатель массива write
      cout++;                 // колличество прочитаных символов
    }
    p_b++; // двигаем указатель byf
  }

  p_w -= cout; // откатвваем указатель (data 16,i 16) (id 25, i 8) (time cout, i 16)   
  for (int i = 1; i <= 16; i++) {
    time = *p_w & 0xF; 
    p_w++;
    time = ; 
  }
  
  printf ("%lu", time); 
  fclose(file);
  return 0;
}
