#include<stdio.h>

void *star(char *input){
    int x = 0;
    while((input[x] <= 'z' && input[x]  >= 'a') ||
        (input[x] <= 'Z' && input[x]  >= 'A')){
            input[x] = '*';
            x++;
        }
}

int main(void){
    char *x = "sdfsdkfl";
    printf("%s %s\n",x,star(x));
    return 0;
}
