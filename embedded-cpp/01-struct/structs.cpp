#include <cstdint>
#include <cstdio>

struct can {
  uint64_t time;
  uint64_t id;
  uint64_t data;
  uint64_t data1;
};

void print_log (can *log)
{		
	log->time++; log->id++; log->data++; log->data1++;
	printf ("%lX %lX %lX %lX\n", log->time, log->id, log->data, log->data1);
	
}
int main(){
	
	can log = {0x1111,0x2222,0x3333,0x4444};
	print_log(&log); 
	return 0;

}
