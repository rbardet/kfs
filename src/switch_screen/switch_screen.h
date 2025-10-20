#include <stdbool.h>
#include <stddef.h>
#include "../debug/printk.h"

#define TERMINAL_COUNT 10

typedef struct s_terminal {
    int active;
    int nb;
    char buffer[HEIGHT + 1][WIDTH + 1];
    int line;
    int column;
    char color;
} t_terminal;

extern t_terminal terminals[TERMINAL_COUNT];

void switch_terminal(int terminal_number);
void save_terminal_state(t_terminal *terminal);
void load_terminal_state(t_terminal *terminal);
void terminal_initialize();