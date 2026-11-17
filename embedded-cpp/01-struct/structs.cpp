#include <cstdint>
#include <cstdio>

int main(int argc, char *argv[]) {
  // проверка ар7ументов командной строки
  if (argc != 2) {
    printf("Проверь аргументы\n");
    return 1;
  }
  // открываем файл
  FILE *file = fopen(argv[1], "rb");
  if (!file) {
    printf("Ошибка: не удалось открыть файл %s\n", argv[1]);
    return 1;
  }
  // берём память на стэке
  char byf[256] = {0};
  char write[256] = {0};

  // запись в память и ноль в конце

  fgets(byf, sizeof(byf), file);
  char *p_b = byf;
  char *p_w = write;

  while (*p_b != '\0') {
    if (*p_b >= '0' && *p_b <= 'F') {
      *p_w = *p_b;
      p_w++;
    }
    p_b++;
  }

  printf("%s\n", write);

  fclose(file);
  return 0;
}
