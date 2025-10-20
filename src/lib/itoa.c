#include "lib.h"

char *itoa(int value, char *str)
{
    char *p = str;
    char *p1, *p2;
    unsigned int ud = value;
    int divisor = 10;

    if (value < 0) {
        *p++ = '-';
        str++;
        ud = -value;
    }
    do {
        int remainder = ud % divisor;
        *p++ = remainder + '0';
        ud /= divisor;
    } while (ud != 0);
    *p = '\0';

    p1 = str;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
    return str;
}