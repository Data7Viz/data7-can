#include <cstdint>
#include <cstdio>

struct can {
  uint32_t time;
  uint16_t id;
  uint8_t data;
};

int main() {
  can log = {0x80000005, 0x8005, 0x85};
  // printf("%b\n%b\n%b\n", log.time, log.id, log.data);

  uint32_t *ref_t = &log.time;
  uint16_t &ref_i = log.id;
  uint8_t &ref_d = log.data;

  printf("%p %b\n", ref_t, *ref_t);
  printf("%p %b\n", (void *)&ref_i, ref_i);
  printf("%p %b\n", (void *)&ref_d, ref_d);

  for (int i = 0; i < 8; i++) {
    ;
  }

  int razm = sizeof(can);
  printf("Структура %d байт\n", razm);
  return 0;
}
