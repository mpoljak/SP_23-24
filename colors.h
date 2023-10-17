#ifndef colors_h
#define colors_h

#include "DefineInclude.h"

void red() {
	printf("\033[1;31m");
}

void cyan() {
	printf("\033[0;36m");
}

void white() {
	printf("\033[0;37m");
}

void purple() {
	printf("\033[0;35m");
}

void yellow() {
	printf("\x1b[33m");
}

void green() {
	printf("\033[0;32m");
}


#endif