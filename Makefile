NAME         = kfs.iso
KERNEL       = kernel
KERNEL_FILE  = kfs/
BOOT_FILE    = kfs/boot/

CC           = gcc
CFLAGS       = -m32 -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs

ASM          = nasm
ASMFLAGS     = -f elf32

LINKER       = linker/linker.ld
LINK_FLAGS   = ld -m elf_i386 -T

BIN          = bin/
OBJ          = obj/
SRC          = src
X86          = $(SRC)/x86
LIB          = $(SRC)/lib
GRAPHIC      = $(SRC)/graphic
KEYB         = ${SRC}/hardware/keyboard
SH           = ${SRC}/shell

C_SOURCES    = $(SRC)/kernel.c \
			   ${SRC}/gdt.c \
			   $(LIB)/khexdump.c \
			   $(LIB)/strlen.c \
			   $(LIB)/itoa.c \
			   $(LIB)/memset.c \
			   $(LIB)/strcmp.c \
			   ${KEYB}/keyboard.c \
			   $(GRAPHIC)/printk.c \
			   ${GRAPHIC}/switch_screen.c \
			   ${SH}/shell.c \
			   ${SH}/command.c \
			   ${SH}/cursor.c

ASM_SOURCES  = $(X86)/boot.s \
			   $(X86)/io.s \
			   $(X86)/stack.s

C_OBJECTS    = $(C_SOURCES:$(SRC)/%.c=$(OBJ)/%.o)
ASM_OBJECTS  = $(ASM_SOURCES:$(SRC)/%.s=$(OBJ)/%.o)

GRUB         = grub-mkrescue # --compress=gz
QEMU         = qemu-system-i386

INCLUDES = -I Includes

all: fclean $(BIN) $(NAME)

$(BIN):
	mkdir -p $@

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c ${INCLUDES} $< -o $@

$(OBJ)/%.o: $(SRC)/%.s
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

$(KERNEL): $(C_OBJECTS) $(ASM_OBJECTS)
	$(LINK_FLAGS) $(LINKER) -o $@  $(ASM_OBJECTS) $(C_OBJECTS)
	mv $@ $(BOOT_FILE)

$(NAME): $(KERNEL)
	$(GRUB) -o $@ $(KERNEL_FILE)
	mkdir -p ${BIN}
	mv $@ $(BIN)

run: $(NAME)
	$(QEMU) $(BIN)/$(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(BOOT_FILE)/$(KERNEL) $(BIN)/$(NAME)

.PHONY: all run clean fclean
