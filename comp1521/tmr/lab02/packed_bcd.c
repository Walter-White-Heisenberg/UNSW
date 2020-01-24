#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    // PUT YOUR CODE HERE

    return (packed_bcd_value & 0xF) + 10 * ((packed_bcd_value >> 4) & 0xF) + 100 * ((packed_bcd_value >> 8) & 0xF)+ 1000 * ((packed_bcd_value >>12) & 0xF)+ 10000 * ((packed_bcd_value >> 16) & 0xF)+100000 * ((packed_bcd_value >> 20) & 0xF)+1000000 * ((packed_bcd_value >> 24) & 0xF)+10000000 * ((packed_bcd_value >> 28) & 0xF);
}
