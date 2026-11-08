#include <cstdio>
#include <cstdint>

struct can {
	uint16_t time;
	uint32_t id;
	uint8_t data [8];
};

int main (){
	can log = {0x8001, 0x80000001, {0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81}};
	printf ("%b\n%b\n", log.time, log.id);
	for (int i = 0; i < 8; i++)
	{
		printf ("%b\n", log.data[i]); 
	}

	return 0;
}
