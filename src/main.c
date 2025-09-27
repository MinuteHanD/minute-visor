/* trying the first entry point */

#include "hypervisor.h"

void hypervisor_main(void){
	serial_init();

	serial_print("hypervisor v0.1 \n");
	serial_print("hardware initialized, running now");

	while(1){
		// main vm loop, just testing boot for now
		asm volatile("hlt");
	}
}
