#include<stdio.h>
int main(void)
{
int x,y,z,i;
printf("Enter number: ");
scanf("%d",&x);
i=2;
z=x;
y=0;
while(i<z)
{
    if(z % i ==0)
    {
        y++;
    }
i++;
}
i=2;
if(y==0)
{
    printf("%d is prime\n",z);
}else
{   printf("The prime factorization of %d is:\n",x); 
while(i<z)
{
    if(z % i ==0)
    {
        z = z / i;
        printf("%d * ",i);
        i--;
    }
i++;
}
    printf("%d",z);        
    printf(" = %d\n",x);
}
return 0;
}
