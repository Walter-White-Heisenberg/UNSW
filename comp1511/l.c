#include<stdio.h>
int main(void)
{
int x;
int i=1;
printf("Enter size: ");
scanf("%d",&x);
    while(i<x)
    {printf("*\n");
    i++;}
    while(0<i){
    printf("*");
    i--;}
    printf("\n");
return 0;
    
}
