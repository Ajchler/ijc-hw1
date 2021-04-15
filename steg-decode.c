// steg-decode.c
// Řešení IJC-DU1, příklad a), 11.3.2021
// Autor: Vojtěch Eichler
// Přeloženo: gcc 10.2.1
// Program na dekódování a nalezení zprávy v .ppm obrazku

#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"
#include "ppm.h"

int main(int argc, char **argv) {
	char to_print = 0;
	int bit_count = 0;

	// if file wasn't given by user or too many arguments were given, then invoke error
	if (argc != 2) {
		error_exit("Nevhodný počet vstupních argumentů");
	}
	
	struct ppm *image = ppm_read(argv[argc - 1]);

	if (!image) {
		error_exit("Chyba při čtení obrazových dat");
	}

	unsigned long size = image->xsize * image->ysize * 3;

	// creating bitset with the same size as picture data
	bitset_alloc(bset, size);
	// applying eratosthenes on the bitset
	Eratosthenes(bset);

	// cycling through bitset
	for (unsigned long i = 23; i < size; i++) {
		// if value is 0, then i is a prime number
		if (bitset_getbit(bset, i) == 0) {
			// setting bit according to a value of LSB in image data at index i
			if (image->data[i] & (char)1) 
				to_print |= ((char)1 << bit_count);
			 else 
				to_print &= ~((char)1 << bit_count);
			bit_count++;
			//printing character if 8 bits were read
			if (bit_count == 8) {
				putchar(to_print);

				//end of a message
				if (to_print == '\0')
					break;
				bit_count = 0;
				to_print = 0;
			}
		}
	}	
	// freeing allocated memory, checking if the message ending was correct
	bitset_free(bset);
	ppm_free(image);
	if (to_print != '\0')
		error_exit("Zpráva není korektně ukončena");
	return 0;
}
