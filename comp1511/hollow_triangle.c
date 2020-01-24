#include<stdio.h>
int main(void)
{
int x;
int i=1;
printf("Enter size: ");
scanf("%d",&x);
    while(i<x)
    {int n=1;
    while(n<=i){if(n==1||n==i){printf("*");}
    else{printf(" ");}
    n++;}
    printf("\n");
    i++;}
    while(0<i){
    printf("*");
    i--;}
    printf("\n");
return 0;
}    
