#include "switch_screen.h"

t_terminal terminals[TERMINAL_COUNT];

void switch_terminal(int terminal_number) {
	if (terminal_number < 0 || terminal_number >= TERMINAL_COUNT) {
		return;
	}

	t_terminal *current_terminal = NULL;
	t_terminal *new_terminal = &terminals[terminal_number];

	for (int i = 0; i < TERMINAL_COUNT; i++) {
		if (terminals[i].active) {
			current_terminal = &terminals[i];
			break;
		}
	}

	if (current_terminal != NULL) {
		save_terminal_state(current_terminal);
		current_terminal->active = 0;
		reset();
	}

	load_terminal_state(new_terminal);
	new_terminal->active = 1;
}

void save_terminal_state(t_terminal *terminal) {
	terminal->line = line;
	terminal->column = column;
	terminal->color = tty_color >> 8;

	char c;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			char c = vga[y * WIDTH + x] & 0xFF;
			if (c == ' ') {
				terminal->buffer[y][x] = 0;
				continue;
			}
			terminal->buffer[y][x] = vga[y * WIDTH + x] & 0xFF;
		}
	}
}

void load_terminal_state(t_terminal *terminal) {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			vga[y * WIDTH + x] = terminal->buffer[y][x] | (terminal->color << 8);
		}
	}

	line = terminal->line;
	column = terminal->column;
	tty_color = terminal->color << 8;
}

void terminal_initialize() {
	for (int i = 0; i < TERMINAL_COUNT; i++) {
		terminals[i].nb = i;
		terminals[i].line = 0;
		terminals[i].column = 0;
		terminals[i].color = COLOR_LIGHT_GREEN;
		terminals[i].active = (i == 0) ? 1 : 0;
		for (int y = 0; y < HEIGHT; y++) {
			for (int x = 0; x < WIDTH; x++) {
				terminals[i].buffer[y][x] = ' ';
			}
		}
	}
	terminals[1].color = COLOR_BLUE;
	terminals[2].color = COLOR_LIGHT_BLUE;
	terminals[3].color = COLOR_BROWN;
	terminals[4].color = COLOR_LIGHT_CYAN;
	terminals[5].color = COLOR_CYAN;
	terminals[6].color = COLOR_LIGHT_RED;
	terminals[7].color = COLOR_RED;
	terminals[8].color = COLOR_WHITE;
	terminals[9].color = COLOR_MAGENTA;
	tty_color = terminals[0].color << 8;
	column = terminals[0].column;
	line = terminals[0].line;
}



