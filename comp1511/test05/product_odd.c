#include<stdio.h>
int main(void)
{
int x,y;
printf("Enter lower: ");
scanf("%d",&x);
printf("Enter upper: ");
scanf("%d",&y);
int i=1;
int p=1;
while(i<(y-x))
    {
    if( ( i + x ) % 2 == 1 )
        {
        p = p * ( i + x );
        }
    i++;
    }
printf("%d\n",p);
return 0;
} 
