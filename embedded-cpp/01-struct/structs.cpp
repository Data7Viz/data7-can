#include <cstdint>
#include <cstdio>

struct can {
  uint32_t time;
  uint16_t id;
  uint8_t data;
};

int main() {
  can log = {0x80000005, 0x8005, 0x85};
  //printf("%b\n%b\n%b\n", log.time, log.id, log.data);
  
  uint8_t *addr = (uint8_t*)&log.time; 

  for (int i = 0; i < 8; i++) {
    printf ("%b  %p\n", *addr, addr);
    addr++; 
  }

  int razm = sizeof(can);
  printf("Структура %d байт\n", razm);
  return 0;
}
