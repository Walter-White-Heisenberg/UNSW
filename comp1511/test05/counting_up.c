#include<stdio.h>
int main(void)
{
int x,y;
printf("Enter lower: ");
scanf("%d",&x);
printf("Enter upper: ");
scanf("%d",&y);
int i=1;
while(i<(y-x))
    {
    printf("%d\n",x+i);
    i++;
    }
return 0;
} 
