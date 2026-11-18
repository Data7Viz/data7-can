#include <cstdint>
#include <cstdio>

int main(int argc, char *argv[]) {
  // открываем файл
  FILE *file = fopen(argv[1], "rb");
  // берём память на стэке
  char byf[128] = {0};
  uint8_t write[128] = {0};
  uint8_t cout = 0;

  // запись в память и ноль в конце
  fgets(byf, sizeof(byf), file);
  char *p_b = byf;
  uint8_t *p_w = write;

  while (*p_b != '\0') {
    if (*p_b >= '0' && *p_b <= '9') {
      *p_w = *p_b - 48;
      p_w++;
      cout++; // колличество прочитаных символов
    } else if (*p_b >= 'A' && *p_b <= 'F') {
      *p_w = *p_b - 'A' + 10; // преобразование символа в число
      p_w++;                  // двигаем указатель массива write
      cout++;                 // колличество прочитаных символов
    }
    p_b++; // двигаем указатель byf
  }

  p_w -= cout; // откатвваем указатель в начало
  for (int i = 0; i < cout; i++) {
    printf("%X", *p_w);
    p_w++;
  }
  printf("\n");
  fclose(file);
  return 0;
}
