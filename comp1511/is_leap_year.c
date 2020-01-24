#include<stdio.h>
int main(void)
{
int y;
printf("Enter year: ");
scanf("%d",&y);
if (y % 4==0&&y<2100&&1999<y){printf("%d is a leap year.\n",y);}
else {printf("%d is not a leap year.\n",y);}
return 0;
 }
