//
// Sample solution for COMP1521 lab exercises
//
// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {
    int i = 1,sum = 0,r = 32768/2;//t for loop, t fot total, r for 1,2,4,8,16... in the loop
    while(i<16){
        sum = sum + (bits[i] == '1') * r;
        r = r / 2;
        i++;
    }
    sum = sum -(bits[0] == '1') * 32768;
    return sum;
}


