#include <stdio.h>
#include<stdint.h>

int main(void){
    int x[5] = {1,2,3,4,5};
    uint64_t m = x[3];
    uint64_t n = x[1];
    printf("%u\n",(uint32_t)(n-m));
}
