// bitset.c
// Řešení IJC-DU1, příklad a), 2.3.2021
// Autor: Vojtěch Eichler
// Přeloženo: gcc 10.2.1

#include "bitset.h"

// if USE_INLINE is defined, use inline functions
#ifdef USE_INLINE
	extern inline void bitset_free(bitset_t jmeno_pole);
	extern inline unsigned long bitset_size(bitset_t jmeno_pole);
	extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index,int vyraz);
	extern inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);
#endif
