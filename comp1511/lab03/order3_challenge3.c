#include<stdio.h>
int main(void)
{
int x;
int y;
int z;
printf("Enter integer: ");
scanf("%d",&x);
printf("Enter integer: ");
scanf("%d",&y);
printf("Enter integer: ");
scanf("%d",&z);
x<=y;
y<=z;
printf("The integers in order are: %d %d %d\n",x,y,z);
return 0;
}
