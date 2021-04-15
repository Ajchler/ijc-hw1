// eratosthenes.c
// Řešení IJC-DU1, příklad a), 6.3.2021
// Autor: Vojtěch Eichler
// Přeloženo: gcc 10.2.1
// Implementace funkce na výpočet Eratosthenova síta

#include <stdlib.h>
#include <math.h>
#include "bitset.h"
#include "eratosthenes.h"

void Eratosthenes(bitset_t pole) {
	bitset_setbit(pole, 0, 1);
	bitset_setbit(pole, 1, 1);

	//for each index with a value of 0, set all it's multiples to 1
	for (unsigned long i = 2; i <= sqrt(bitset_size(pole)); i++) {
		if (!(bitset_getbit(pole,i))) {
			for (unsigned long j = 2*i; j < bitset_size(pole); j += i) {
				bitset_setbit(pole, j, 1);
			}
		}
	}
}
