include vars.mk
include color.mk

all: fclean $(BIN) $(NAME)

$(BIN):
	@echo "$(BLUE)[MKDIR] Creating binary folder: $@$(RESET)"
	@mkdir -p $@

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[CC] Compiling C file: $<$(RESET)"
	@$(CC) $(CFLAGS) -c ${INCLUDES} $< -o $@
	@echo "$(GREEN)[CC] OK -> $@$(RESET)"

$(OBJ)/%.o: $(SRC)/%.s
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[AS] Assembling ASM file: $<$(RESET)"
	@$(ASM) $(ASMFLAGS) $< -o $@
	@echo "$(GREEN)[AS] OK -> $@$(RESET)"

$(KERNEL): $(C_OBJECTS) $(ASM_OBJECTS)
	@echo "$(BLUE)[LD] Linking kernel: $@$(RESET)"
	@$(LINK_FLAGS) $(LINKER) -o $@  $(ASM_OBJECTS) $(C_OBJECTS)
	@echo "$(GREEN)[LD] Kernel linked$(RESET)"
	@mv $@ $(BOOT_FILE)

$(NAME): $(KERNEL)
	@echo "$(BLUE)[GRUB] Generating bootable image: $@$(RESET)"
	@$(GRUB) -o $@ $(KERNEL_FILE)
	@mkdir -p ${BIN}
	@mv $@ $(BIN)
	@echo "$(GREEN)[GRUB] Image created: $(BIN)/$@$(RESET)"

run: $(NAME)
	@echo "$(BLUE)[QEMU] Launching: $(BIN)/$(NAME)$(RESET)"
	$(QEMU) $(BIN)/$(NAME)

clean:
	@echo "$(RED)[RM] Cleaning objects...$(RESET)"
	@rm -rf $(OBJ)
	@echo "$(GREEN)[RM] Objects cleaned$(RESET)"

fclean: clean
	@echo "$(RED)[RM] Cleaning binaries...$(RESET)"
	@rm -f $(BOOT_FILE)/$(KERNEL) $(BIN)/$(NAME)
	@echo "$(GREEN)[RM] All cleaned$(RESET)"

.PHONY: all run clean fclean
