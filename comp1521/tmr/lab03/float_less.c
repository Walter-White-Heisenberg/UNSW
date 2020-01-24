// Compare 2 floats using bit operations only

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
    uint32_t sign1 = bits1>>31;
    uint32_t power1 = (bits1 >> 23) & 0xFF;
    uint32_t flo1 = bits1 & 0x7FFFFF;
    uint32_t sign2 = bits2>>31;
    uint32_t power2 = (bits2 >> 23) & 0xFF;
    uint32_t flo2 = bits2 & 0x7FFFFF;
    if(flo2 == 0 && power1 == 0 && power2 == 0 && flo1 == 0) return 0;
    else if(power1 == 0xFF && power2 == 0xFF && flo1 + flo2 != 0) return 0;
    else if(sign1 == 1 && sign2 == 0) return 1;
    else if(sign1 == 0 && sign2 == 1) return 0;
    else if(power1 > power2  && power1 != power2) return sign1;
    else if(power1 < power2  && power1 != power2) return !(sign1);
    else if(flo1 == flo2) return 0;
    else if(flo1 > flo2 && sign1 == 1) return 1;
    else if(flo1 < flo2 && sign1 == 0) return 1;
    
    

    return 0;
}
