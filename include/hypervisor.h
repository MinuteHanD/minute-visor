// will be doing all core definitions here

#ifndef HYPERVISOR_H
#define HYPERVISOR_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

// I/O
static inline void outb(uint16_t port){
	uint8_t value;
	asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

void hypervisor_main(void);
void serial_init(void);
void serial_print(const char* str);

#endif

