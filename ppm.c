// ppm.c
// Řešení IJC-DU1, příklad b), 10.3.2021
// Autor: Vojtěch Eichler
// Přeloženo: gcc 10.2.1
// Implementace funkce pro načtení dat do struktury definované v ppm.h
// a funkce na uvolnění paměti alokované pro tuto strukturu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "error.h"
#include "ppm.h"

struct ppm* ppm_read(const char *filename) {
	unsigned x = 0;
	unsigned y = 0;
	unsigned max_color = 0;
	char fmt[3];

	FILE *f = fopen(filename, "r");

	// checking if opening file failed
	if (!f) {
		warning_msg("Nepodařilo se otevřít soubor");
		return NULL;
	}
	
	// scaning file header, if fscanf fails to load all 4 values, invokes warning
	if (fscanf(f, "%s %u %u %u", fmt, &x, &y, &max_color) != 4) {
		warning_msg("Formát je chybný");
		fclose(f);
		return NULL;
	}
	
	// testing if format is P6
	if (strcmp(fmt, "P6") != 0) {
		fclose(f);
		warning_msg("Formát je chybný");
		return NULL;
	}

	if (x == 0 || y == 0) {
		fclose(f);
		warning_msg("Velikosti obrázku nesmí být 0");
		return NULL;
	}
	
	// if the size of data is higher than limit defined in ppm.h
	if ((x * y * 3) > SIZE_LIMIT) {
		warning_msg("Obrazová data jsou příliš velká");
		fclose(f);
		return NULL;
	}
	
	// invoking warning if max color value is greater than 255 or less or equal than 0
	if (max_color > UCHAR_MAX || max_color == 0) {
		warning_msg("Chybně zadaná maximální hodnota barvy");
		fclose(f);
		return NULL;
	}
	
	// expecting a whitespace at the end of header
	int c = fgetc(f);
	if (!isspace(c)) {
		warning_msg("Hlavička není zakončena bilym znakem");
		fclose(f);
		return NULL;
	}

	// allocating size of structure + size of array
	struct ppm *image = malloc(sizeof(struct ppm) + (x * y * 3));
	
	// checking if allocation succeeded
	if (!image) {
		warning_msg("Chyba alokace struktury");
		fclose(f);
		return NULL;
	}
	
	// inserting values into the structure
	image->xsize = x;
	image->ysize = y;
	if (fread(image->data, 1, x * y * 3, f) != x * y * 3) {
		warning_msg("Načtení dat se nezdařilo");
		fclose(f);
		ppm_free(image);
		return NULL;
	}

	fclose(f);
	return image;
}

void ppm_free(struct ppm *p) {
	free(p);
}
