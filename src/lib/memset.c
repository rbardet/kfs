#include "lib.h"

void	*memset(void *s, int c, size_t n) {
	char unsigned *str = (char unsigned *) s;
	size_t a = 0;

	while (n != 0) {
		str[a] = c;
		a++;
		n--;
	}

	return (s);
}
