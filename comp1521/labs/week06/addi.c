// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    return ((uint32_t)1 << 29) + (((uint32_t)t & 0x1F) << 16) + (((uint32_t)s & 0x1F) << 21) + ((uint16_t)i); // REPLACE WITH YOUR CODE
}
