/* serial communication module
 * handles basic I/O
 */

#include "hypervisor.h"
#include <bits/types/stack_t.h>

#define SERIAL_COM1 0X3F8

void serial_init(void){
	outb(SERIAL_COM1 + 1, 0X00);
	outb(SERIAL_COM1 + 3, 0X80);

	outb(SERIAL_COM1 + 0, 0X03);
	outb(SERIAL_COM1 + 1, 0X00);

	// 8 BITS, NO PARITY, ONE STOP BIT
	outb(SERIAL_COM1 + 3, 0x03);
	// ENABLE FIFO
	outb(SERIAL_COM1 + 2, 0xC7);
	// ENABLE IRQ
	outb(SERIAL_COM1 + 4, 0x0B);
}

static void serial_putchar(char c){
	while ((inb(SERIAL_COM1 + 5) & 0X20) == 0);
	outb(SERIAL_COM1, c);
}

void serial_print(const char* str){
	while (*str){
		if (*str == '\n'){
			serial_putchar('\r'); // carriage return
		}
		serial_putchar(*str++);
	}
}

