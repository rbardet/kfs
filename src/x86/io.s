global inb
global outb
global outw
global halt
inb:
	mov edx, [esp + 4]
	in al, dx
	ret

outb:
	mov eax, [esp + 4]
	mov edx, [esp + 8]
	out dx, al
	ret

outw:
	mov eax, [esp + 4]
	mov edx, [esp + 8]
	out dx, ax
	ret

halt:
	hlt