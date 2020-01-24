// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -int, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    uint32_t sign = f >> 31;
    uint32_t power = (f >> 23) & 0xFF;
    uint32_t flo = f & 0x7FFFFF;
    if(power == 0xFF || (power == 0 && flo == 0)) return f;
    else if(11 + power >= 0xFF) return (sign << 31) + (0xFF << 23);
    else return flo | ((power + 11) << 23) | (sign << 31);
}
