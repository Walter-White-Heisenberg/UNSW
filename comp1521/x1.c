#include<stdio.h>


void sum(int a){
    a = 5;
}
int main(void){
    int x = 1;
    printf("%d\n",x);
    sum(x);
    printf("%d\n",x);    
}

