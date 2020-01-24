#include<stdio.h>
int main(void)
{
int array[3]={1};
array[1]=213;
array[2]=33;
array[0]=32;
printf("%d",array[0]);
}
