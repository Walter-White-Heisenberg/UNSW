#include<stdio.h>
int main(void)
{int x;
int i=0;
printf("Enter number: ");
scanf("%d",&x);
while(i < x-1){i=i+1;
if(i % 3==0 || i % 5==0)printf("%d\n",i);}
return 0;
}
