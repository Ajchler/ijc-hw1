// ppm.h
// Řešení IJC-DU1, příklad b), 10.3.2021
// Autor: Vojtěch Eichler
// Přeloženo: gcc 10.2.1
// Hlavičkový soubor s definicí datové struktury a základních funkcí
// k práci se soubory .ppm

struct ppm {
	unsigned xsize;
	unsigned ysize;
	char data[];
};

#define SIZE_LIMIT 8000*8000*3

struct ppm* ppm_read(const char *filename);

void ppm_free(struct ppm *p);
