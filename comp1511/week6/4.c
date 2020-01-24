#include<stdio.h>
int main(void){
    char c;
    c = getchar();
    while(c != EOF){
        printf("character %c gets a ASCII code value as %d\n",c,c);      
        c = getchar();

    }
    

}
