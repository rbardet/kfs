section .text
	ALIGN 4
	DD 0x1BADB002
	DD 0x00000000
	DD -(0x1BADB002 + 0x00000000)

global start
global load_gdt
extern kmain
start:
	CALL kmain

load_gdt:
	mov eax, [esp + 4]
	lgdt [eax]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ax, 0x18
	mov ss, ax
	JMP 0x08:.reload
	ret
.reload:
	ret

load_idt:
	mov eax, [esp + 4]
	lidt [eax]
	ret