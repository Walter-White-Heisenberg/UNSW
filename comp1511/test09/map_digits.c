#include<stdio.h>
int main(int argc, char *argv[]){   
    char x;
    x = getchar();
    while(x != EOF){
        if((x < 58) * (x > 47) > 0){
            putchar(argv[1][x-48]);
        }else{
            putchar(x);
        }
        x = getchar();
    }
    return 0;
}

