global inb
global outb
global outw
global halt

inb:
	mov edx, [esp + 4]
	in al, dx
	ret

outb:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, al
	ret

outw:
	mov edx, [esp + 4]
	mov eax, [esp + 8]
	out dx, ax
	ret

halt:
	hlt