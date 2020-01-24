#include<stdio.h>
#include<stdint.h>
int main(void){
    float x = 0;
    for(int i = 31; i > 0; i--)
        printf("%d",(uint32_t)x & ((uint32_t)1 << i));
    printf("\n");
}
