#include<stdio.h>
int main(void)
{
int x;
int y;
printf("Please enter two integers: ");
scanf("%d",&x);
printf(" ");
scanf("%d",&y);
int z=x+y;
printf("%d + %d = %d\n",x,y,z);
return 0;
}
