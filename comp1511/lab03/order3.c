#include<stdio.h>
int main(void)
{
int x,y,z;
printf("Enter integer: ");
scanf("%d",&x);
printf("Enter integer: ");
scanf("%d",&y);
printf("Enter integer: ");
scanf("%d",&z);
printf("The integers in order are: ");
if (x<=y&&x<=z){printf("%d ",x);
if(y<=z){printf("%d %d\n",y,z);}
else printf("%d %d\n",z,y);}
else if (y<=x&&y<=z){printf("%d ",y);
if(x<=z){printf("%d %d\n",x,z);}
else printf("%d %d\n",z,x);}
else if (z<=y&&z<=x){printf("%d ",z);
if(y<=x){printf("%d %d\n",y,x);}
else printf("%d %d\n",x,y);}
return 0;}
