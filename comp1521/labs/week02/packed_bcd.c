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
    int m = 1+2+4+8;
    return ((packed_bcd_value >> 28) & m) * 10000000 + ((packed_bcd_value >> 24) & m) * 1000000 + ((packed_bcd_value >> 20) & m) * 100000
    + ((packed_bcd_value >> 16) & m) * 10000 + ((packed_bcd_value >> 12) & m) * 1000 + ((packed_bcd_value >> 8) & m) * 100 + ((packed_bcd_value >> 4) & m) * 10 + (packed_bcd_value & m);
}
