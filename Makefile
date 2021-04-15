# Makefile
# Řešení IJC-DU1, 11.3.2021
# Autor: Vojtěch Eichler
# Přeloženo: gcc 10.2.1
# makefile pro sestavení primes, primes-i a steg-encode
# make run zároveň spustí primes a primes-i, a make clean
# smaže .o soubory

CC = gcc
CFLAGS =-g -O2 -std=c11 -pedantic -Wall -Wextra
LDFLAGS = -lm
LC_ALL = cs_CZ.utf8

all: primes primes-i steg-decode

run: primes primes-i
	./primes
	./primes-i

# STEG-DECODE, UKOL b)
steg-decode: bitset.o error.o eratosthenes.o ppm.o steg-decode.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

steg-decode.o: steg-decode.c
	$(CC) $(CFLAGS) -c $^ -o $@

ppm.o: ppm.c
	$(CC) $(CFLAGS) -c $^ -o $@

# PRIMES, UKOL a)
primes: primes.o bitset.o eratosthenes.o error.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

primes.o: primes.c
	$(CC) $(CFLAGS) -c $^ -o $@

bitset.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -c $< -o $@

eratosthenes.o: eratosthenes.c eratosthenes.h
	$(CC) $(CFLAGS) -c $< -o $@

# inline variant of primes
primes-i: primes-i.o bitset-i.o eratosthenes-i.o error.o
	$(CC) $(CFLAGS)  $^ -o $@ $(LDFLAGS)

primes-i.o: primes.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c $^ -o $@

bitset-i.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@

eratosthenes-i.o: eratosthenes.c eratosthenes.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c $< -o $@

# ERROR
error.o: error.c error.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o
