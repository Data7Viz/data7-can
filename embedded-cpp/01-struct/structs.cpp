#include <cstdint>
#include <cstdio>

struct canframe {
	uint64_t sec; // секунды
	uint32_t mic_sec; // микросекунды
	uint32_t id; // индификатор 
	uint32_t pgn; // номер группы параметров 
	uint8_t data [8]; // поле данных 
	uint8_t byte_1; // голова 
	uint8_t addr_su; // адрес источника
	uint8_t addr_ds; // адрес назначения
	uint8_t prior; // приоритет сообщения 

// битовый метод сдвигаю вытягиваю данные
	void can_bit () {
		prior = (id >> 26) & 0x7;  // вытягиваем приоритет
		byte_1 = (id >> 16) & 0xFF; // вытягиваем 1 байт чтоб определить адресное или вещательное сообщение 
		addr_su = id & 0xFF; // адрес бллок источник 

		if (byte_1 < 240) {
			addr_ds = (id >> 8) & 0xFF; // вытягиваем блок назначения
		} else {
			pgn = (id >> 8) & 0x3FFFF;
		}
	}
// метод печати 
	void print () {
		if (addr_su == 238){
			printf (" PGN %04X Источ %03u ", pgn, addr_su);  
			for (int i = 0; i < 8; i++) printf (" %02X", data[i]); 
			printf ("\n"); 
	}
	
	} 
}; 

int main(int argc, char *argv[]) {
  // открываем файл
  FILE *file = fopen(argv[1], "rb");
  // берём память на стэке
  char byf[128] = {0}; 

  while (fgets(byf, sizeof(byf), file) != 0) { // ложим строку на стэ
	
	canframe log = {}; // создали обьект внутри цикла для обнуления переменных

	// чистим фрейм и присваиваем значение 	
	sscanf(byf, " (%lu.%u) %*s %x [%*d] %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx",&log.sec, &log.mic_sec, &log.id,
			&log.data[0], &log.data[1], &log.data[2], &log.data[3], &log.data[4], &log.data[5], &log.data[6], &log.data[7]);

	log.can_bit (); 
	log.print (); 
  } 

  return 0;
}
