#include<stdio.h>
int main(void){
    char x;
    x = getchar();
    while(x != EOF){
        if((x - 10)*(x - 32) == 0 || (x < 58) * (x > 47) > 0){
            putchar(x);
        }else{
            putchar('.');
        }
        x = getchar();
    }
    return 0;
}

