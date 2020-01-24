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
    uint32_t As = bits1 >> 31, Ae = (bits1 >> 23) & (1+2+4+8+16+32+64+128), Af = bits1 & 0x7FFFFF;
    uint32_t Bs = bits2 >> 31, Be = (bits2 >> 23) & (1+2+4+8+16+32+64+128),Bf = bits2 & 0x7FFFFF;
    if((Ae == 0xFF && Af != 0) || (Be == 0xFF && Bf != 0))
        return 0;
    else if(Bs == 0 && Be == 0xFF && Bf == 0 && (Ae != 0xFF && Af != 0))
        return 1;
    else if(As == 1 && Bs == 0)
        return 1;
    else if(As == 1 && Bs == 1){
        if(Ae > Be)
            return 1;
        else if(Ae == Be && Af > Bf)
            return 1;
    }else if(As == 0 && Bs == 0){
        if(Ae < Be)
            return 1;
        else if(Ae == Be && Af < Bf)
            return 1;
    }
    return 0;        
}
