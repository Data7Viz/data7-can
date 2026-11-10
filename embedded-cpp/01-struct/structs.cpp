#include <cstdint>
#include <cstdio>

struct can {
  uint32_t time;
  uint16_t id;
  uint8_t data;
};

int main() {
  can log = {0x80000001, 0x8001, 0x81};
  printf("%b\n%b\n%b\n", log.time, log.id, log.data);

  for (int i = 0; i < 8; i++) {
    ;
  }

  int razm = sizeof(can);
  printf("Структура %d байт\n", razm);
  return 0;
}
