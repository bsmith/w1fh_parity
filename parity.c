#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/* Reference:
 * http://graphics.stanford.edu/~seander/bithacks.html#ParityNaive
 */

bool parity_naive(uint8_t v) {
	bool parity = false;
	while (v) {
		parity = !parity;
		v = v & (v - 1);
	}
	return parity;
}

bool parity_64mulmod(uint8_t b) {
	return (((b * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
}

bool parity_shifts(uint8_t b) {
	int v = b;
	v ^= v >> 4;
	v ^= v >> 2;
	v ^= v >> 1;
	return v & 1;
}

bool parity_parallel(uint8_t b) {
	int v = b;
	v ^= v >> 4;
	v &= 0xf;
	return (0x6996 >> v) & 1;
}

int main(int argc, char **argv) {
	uint8_t n = 0;
	do {
		bool actual = parity_naive(n);
		assert(actual == parity_64mulmod(n));
		assert(actual == parity_shifts(n));
		assert(actual == parity_parallel(n));
	} while (++n);
	return 0;
}
