#include <cstdint>
#include <cstdio>

struct can {
  uint32_t time;
  uint16_t id;
  uint8_t data;
};

int main() {
  can log [3] = {0};
  can (&ref)[3] = log; 
  for (int i = 0; i < 3; i ++)
  {
	  log [i] = {1,2,3};
	  printf ("%u %u  %u\n", log[i].time, log[i].id, log[i].data); 
  }

  return 0;
}
