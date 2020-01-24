#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    uint32_t m = 0,a = 0;
    n_rotations = n_rotations % 16 + (n_rotations < 0) * 16;
    m = (uint32_t)bits << n_rotations;
    a = 0xFFFF & (m >> 16);
    m = m & 0xFFFF;
    return (uint16_t)(a + m); //REPLACE ME WITH YOUR CODE

}

