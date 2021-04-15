// bitset.h
// Řešení IJC-DU1, příklad a), 2.3.2021
// Autor: Vojtěch Eichler
// Přeloženo: gcc 10.2.1
// Hlavičkový soubor pro práci s bitovým polem

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "error.h"

#ifndef BITSET_H

#define BITSET_H
typedef unsigned long bitset_t[];
typedef unsigned long bitset_index_t;

// number of bits in unsigned long
#define BITS_IN_UL (sizeof(unsigned long) * CHAR_BIT)

// get number of unsigned longs needed to nest a number of bits
#define get_ul_size(velikost) (((velikost)/BITS_IN_UL) + ((velikost) % BITS_IN_UL ? 1 : 0) + 1)

// creating a mask with bit offset
// implemented as if index 0 is on MSB (most significant bit)
#define mask_with_offset(index) (1UL << (BITS_IN_UL - (index % BITS_IN_UL) - 1))

#define bitset_create(jmeno_pole, velikost)\
	unsigned long jmeno_pole[get_ul_size(velikost)] = {(velikost), 0};\
	static_assert((velikost) > 0, "Velikost pole musi byt vetsi nez 0")

// dynamically allocated bitset, if allocation fails, exit
#define bitset_alloc(jmeno_pole, velikost) \
	assert(velikost > 0);\
	unsigned long *jmeno_pole = calloc(get_ul_size(velikost), sizeof(unsigned long)); \
	if (jmeno_pole == NULL) { \
		fprintf(stderr,"bitset_alloc: Chyba alokace paměti"); \
		exit(1); \
	} \
	jmeno_pole[0] = velikost
	
	#ifndef USE_INLINE
		// freeing memory allocated by bitste_alloc
		#define bitset_free(jmeno_pole) \
			free(jmeno_pole)

		// bitset size is stored at first position in an array
		#define bitset_size(jmeno_pole) \
			jmeno_pole[0]
		
		// setting either 1 or 0 into bitset at index,
		// first ternary operator decides if index is valid, second one uses binary operators
		#define bitset_setbit(jmeno_pole, index, vyraz) \
			(index >= bitset_size(jmeno_pole)) ? \
				error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole) - 1), 0 : \
				(vyraz == 0 ? \
						(jmeno_pole[index / BITS_IN_UL + 1] &= ~(mask_with_offset(index))) : \
						(jmeno_pole[index / BITS_IN_UL + 1] |=  (mask_with_offset(index))))
		// by using binary operators, bitset_getbit returns either a 1 or 0,
		// using ',' (comma) operator to invoke error and return 0
		#define bitset_getbit(jmeno_pole, index) \
			(index >= bitset_size(jmeno_pole)) ? \
				error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole) - 1), 0 : \
				(((jmeno_pole[index / BITS_IN_UL + 1] & (mask_with_offset(index))) > 0)? 1 : 0)
	
	// inline functions, used when USE_INLINE is defined
	#else
		// same implementation as macros above, with some tweaks using if statements instead of
		// ternary operator
		inline void bitset_free(bitset_t jmeno_pole) {
			free(jmeno_pole);
		}

		inline unsigned long bitset_size(bitset_t jmeno_pole) {
			return jmeno_pole[0];
		}

		inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz) {
			if (index >= bitset_size(jmeno_pole)) {
				error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole) - 1);
			}
			vyraz == 0 ? (jmeno_pole[index / BITS_IN_UL + 1] &= ~(mask_with_offset(index))) : 
						 (jmeno_pole[index / BITS_IN_UL + 1] |=  (mask_with_offset(index)));
		}
		inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
			if (index >= bitset_size(jmeno_pole)) {
				error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)index, (unsigned long)bitset_size(jmeno_pole) - 1);
			}
			return ((jmeno_pole[index / BITS_IN_UL + 1] & (mask_with_offset(index))) > 0)? 1 : 0;
		}

	#endif

#endif
