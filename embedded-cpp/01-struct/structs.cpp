#include <cstdint>
#include <cstdio>

int main(int argc, char *argv[]) {
  // открываем файл
  FILE *file = fopen(argv[1], "rb");
  // берём память на стэке
  char byf[128] = {0};
  uint8_t write[128] = {0};
  uint8_t cout = 0, i = 0;
  uint64_t time = 0, data = 0;
  uint32_t id = 0;
  while (fgets(byf, sizeof(byf), file) != 0) { // ложим строку на стэ
    char *p_b = byf;                           // берём 0 адрес byf
    uint8_t *p_w = write;                      // берём 0 адрес write
    cout = 0;                                  // обнуляем счётчик

    // идём до конца строки чистим и выводим числа
    while (*p_b != '\0') {
      if (*p_b >= '0' && *p_b <= '9') {
        *p_w = *p_b - 48; // преобразование символа в число + запись в write
        p_w++;            // двигаем указатель массива write
        cout++;           // колличество прочитаных символов
      } else if (*p_b >= 'A' && *p_b <= 'F') {
        *p_w = *p_b - 'A' + 10; // преобразование символа в число
        p_w++;                  // двигаем указатель массива write
        cout++;                 // колличество прочитаных символов
      }
      p_b++; // двигаем указатель byf
    }
    time = 0;
    id = 0;
    data = 0;
    i = 0;
    p_w -= cout; // откатвваем указатель
    // читаем время
    while (i < 16) {
      time = (time << 3) + (time << 1) + *p_w;
      p_w++;
      i++;
    }
    p_w++; // прыгаем через 0
    // читаем индификатор
    while (i < 24) {
      id = (id << 4) | (*p_w & 0xF);
      p_w++;
      i++;
    }
    p_w++; // прыгаем через 8
    // читаем поле данных
    while (i < 42) {
      data = (data << 4) | (*p_w & 0xF);
      p_w++;
      i++;
    }
    printf("%lu %08X %016lX\n", time, id, data);
  }
  fclose(file);
  return 0;
}
