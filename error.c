// error.c
// Řešení IJC-DU1, příklad b), 8.3.2021
// Autor: Vojtěch Eichler
// Přeloženo: gcc 10.2.1
// modul error.c pro vypsani CHYBY a v pripade error_exit i ukoncil beh programu

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "error.h"

void warning_msg(const char *fmt, ...) {
	va_list args;
	// initializing args with arguments given by user
	va_start(args, fmt);
	fprintf(stderr, "CHYBA: ");
	//printing arguments according to the format given by user in *fmt
	vfprintf(stderr, fmt, args);
	va_end(args);
}

void error_exit(const char *fmt, ...) {
	va_list args;
	//initializing args
	va_start(args, fmt);
	fprintf(stderr, "CHYBA: ");
	//printing arguments in a format given by user
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}
