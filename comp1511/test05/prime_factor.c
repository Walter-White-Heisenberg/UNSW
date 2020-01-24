#include<stdio.h>
int main(void)
{
int x,y,z,i;
printf("Enter number: ");
scanf("%d",&x);
i=2;
z=x;
y=0;

int array[x];
while(i<z)
{
    if(z % i ==0)
    {
        z = z / i;
        array[y]=i;
        i--;
        y++;
    }
i++;
}
array[y+1]=array[y];
i=0;
if(z==x)
{
    printf("%d is prime\n",z);
}else
{   printf("The prime factorisation of %d is:\n",x); 
        while(i<y)
        {   
            printf("%d",array[i]);
            if(i<y)
            {
                printf(" * ");
            }
        i++;
        }
    printf("%d",z);        
    printf(" = %d\n",x);
}
return 0;
}
