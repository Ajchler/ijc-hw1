// error.h
// Řešení IJC-DU1, příklad b), 8.3.2021
// Autor: Vojtěch Eichler
// Přeloženo: gcc 10.2.1
// Hlavičkový soubor k modulu error.c

#ifndef ERROR
#define ERROR

void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif
