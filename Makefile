NAME         = kfs.iso
KERNEL       = kernel
KERNEL_FILE  = kfs/
BOOT_FILE    = kfs/boot/

CC           = gcc
CFLAGS       = -m32 -Wall -Wextra -Werror -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs

ASM          = nasm
ASMFLAGS     = -f elf32

LINKER       = linker/linker.ld
LINK_FLAGS   = ld -m elf_i386 -T

BIN			 = bin/
SRC          = src
X86			 = src/x86
STRING		 = src/lib/string
TERMINAL	 = src/graphic/terminal

C_SOURCES    = $(SRC)/kernel.c \
${STRING}/ft_strlen.c \
${TERMINAL}/print.c

ASM_SOURCES  = $(X86)/boot.s

C_OBJECTS    = $(patsubst %.c,%.o,$(C_SOURCES))
ASM_OBJECTS  = $(patsubst %.s,%.o,$(ASM_SOURCES))

GRUB         = grub-mkrescue
QEMU         = qemu-system-i386

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.s
	${ASM} ${ASMFLAGS} $< -o $@

${KERNEL}: ${C_OBJECTS} ${ASM_OBJECTS}
	${LINK_FLAGS} ${LINKER} -o ${KERNEL} ${C_OBJECTS} ${ASM_OBJECTS}
	mv ${KERNEL} ${BOOT_FILE}

${NAME}: ${KERNEL}
	${GRUB} -o ${NAME} ${KERNEL_FILE}
	mv ${NAME} ${BIN}

run: ${NAME}
	${QEMU} ${BIN}/${NAME}

clean:
	rm -f ${C_OBJECTS} ${ASM_OBJECTS}

fclean: clean
	rm -f ${KERNEL}

.PHONY: all run clean fclean
