global inb
global outb
global outw
global halt
inb:
	MOV edx, [esp + 4]
	IN al, dx
	RET

outb:
	MOV eax, [esp + 4]
	MOV edx, [esp + 8]
	OUT dx, al
	RET

outw:
	MOV eax, [esp + 4]
	MOV edx, [esp + 8]
	OUT dx, ax
	RET

halt:
	hlt