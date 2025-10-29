section .text
	ALIGN 4
	DD 0x1BADB002
	DD 0x00000000
	DD -(0x1BADB002 + 0x00000000)

global start
global inb
global outb
global load_gdt
extern kmain

start:
	;CLI ; disable interrupt
	CALL kmain
; askip c'est dangereux de les laisser pendant 
; le setup de la gdt :
; https://wiki.osdev.org/GDT_Tutorial#How_to_Set_Up_The_GDT

inb:
	MOV edx, [esp + 4]
	IN al, dx
	RET

outb:
	MOV eax, [esp + 4]
	MOV edx, [esp + 8]
	OUT dx, al
	RET

load_gdt:
	MOV eax, [esp + 4]
	LGDT [eax]
	CALL reload_segments
	STI
	RET

reload_segments:
	JMP 0x08:.reload
.reload:
	MOV ax, 0x10
	MOV ds, ax
	MOV es, ax
	MOV fs, ax
	MOV gs, ax
	MOV ss, ax
	RET