#include <cstdint>
#include <cstdio>
#include <vector>

struct can_frame {
  uint64_t sec;
  uint32_t usec;
  uint32_t id;
  uint32_t pgn;
  uint8_t byte_1;
  uint8_t src; // источник
  uint8_t dst; // назначение
  uint8_t prior;
  uint8_t d[8];

  // Один метод прямо внутри для разбора ID
  void parse_id() {
    byte_1 = (id >> 16) & 0xFF;
    src = id & 0xFF;
    prior = (id >> 26) & 0x7;

    if (byte_1 < 240) {
      dst = (id >> 8) & 0xFF;
      pgn = 0;
    } else {
      dst = 0xFF;
      pgn = (id >> 8) & 0xFFFF;
    }
  }
};

int main(int argc, char *argv[]) {
  FILE *file = fopen(argv[1], "rb");
  std::vector<can_frame> frames;
  char buf[128] = {};

  while (fgets(buf, sizeof(buf), file)) {
    can_frame f = {};
    sscanf(buf,
           " (%lu.%u) %*s %x [%*d] %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx",
           &f.sec, &f.usec, &f.id, &f.d[0], &f.d[1], &f.d[2], &f.d[3], &f.d[4],
           &f.d[5], &f.d[6], &f.d[7]);

    f.parse_id();
    frames.push_back(f);
  }
  fclose(file);

  // Дальше работаешь напрямую: одна точка, никаких матрёшек
  for (const auto &f : frames) {
    if (f.src == 238) {
      printf("%lu.%u %X\n", f.sec, f.usec, f.pgn);
    }
  }

  return 0;
}
