#include <stdio.h>
#include <stdint.h>

extern void initialise_monitor_handles(void);

uint8_t current_task = 1;
int main(){
	 //char *p="RajeshwarRS";
	 initialise_monitor_handles();
    printf("Hey Rajeshwar \n");
	return 0;
}
