#include "print.h"

void print_terminal(const char *text, int forecolour, int backcolour) {
    (void)forecolour;
    (void)backcolour;
    char *vmem = VRAM;
    int i = 0;
    int len = ft_strlen(text);
    while (i < len * 2) {
        vmem[i] = text[i];
        i += 2;
    }
    return ;
}