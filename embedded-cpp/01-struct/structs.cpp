#include <cstdint>
#include <cstdio>

struct can {
  uint32_t time;
  uint16_t id;
  uint8_t data;
};

void print_log (can log [])
{
	for (int i = 0; i < 10; i++)
	{
		log[i].time++; 
		log[i].id++; 
		log[i].data++;
		
		printf ("%X %X %X\n", log[i].time, log[i].id, log[i].data);
	}
}
int main(){
	
	can log [10] = {}; 
	uint32_t t = 0x80000001; uint16_t i = 0x8001; uint8_t d = 0x81;
	
	for (int j = 0; j < 10; j++)
	{
		log[j].time = t; 
		log[j].id = i; 
		log[j].data = d;
		
		t++; i++; d++;
		
		printf ("%X %X %X\n", log[j].time, log[j].id, log[j].data);
	}

	print_log(log); 
	return 0;

}
