section .multiboot
	MULTIBOOT2_MAGIC equ 0xe85250d6

	align 8
	dd MULTIBOOT2_MAGIC
	dd 0	; i386 architecture
	dd header_end - header_start
	dd -(MULTIBOOT2_MAGIC + 0 + (header_end - header_start))

	dw 0
	dw 0
	dd 8

header_start:
header_end:

section .text
global _start

_start:
	; trying with 32 bit mode
	mov esp, stack_top

	cli

	extern hypervisor_main
	call hypervisor_main

	cli
.hang:
	hlt
	jmp .hang

section .bss
	resb 16384	; 16kb stack
stack_top:
