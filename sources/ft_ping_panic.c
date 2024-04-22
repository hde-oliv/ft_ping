#include "ft_ping.h"

void panic(char *func) {
	if (func) perror(func);
	exit(1);
}
