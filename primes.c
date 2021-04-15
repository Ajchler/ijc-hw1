// primes.c
// Řešení IJC-DU1, příklad a), 7.3.2021
// Autor: Vojtěch Eichler
// Přeloženo: gcc 10.2.1
// Program pro vypsání posledních deseti prvočísel od 2 do 200 milionů

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "eratosthenes.h"
#include "bitset.h"

int main(void) {
	clock_t start = clock();
	int count = 0;
	unsigned long i = 0;
	// index 0 represents number 0, size has to be 200 000 000 + 1 bits to represent numbers including 200 000 000,
	// stack size increase is usually needed (ulimit -s)
	bitset_create(p, 10800);
	
	Eratosthenes(p);
	// get an index of 10th prime number from the end
	for (i = bitset_size(p) - 1; count < 10; i--) {
		if (!(bitset_getbit(p, i))) {
			count++;
		}
	}
	
	// printing last 10 prime numbers
	for (unsigned long j = i; j < bitset_size(p); j++) {
		if (!(bitset_getbit(p, j))) {
			printf("%lu\n", j);
		}
	}

	// printing program runtime:
	fprintf(stderr, "Time=%.3g\n", (double) (clock() - start) / CLOCKS_PER_SEC);
	return 0;
}
