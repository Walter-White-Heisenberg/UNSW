#include<stdio.h>
int main(void)
{int x;
    printf("Enter your age: ");
    scanf("%d",&x);
    if (16<=x)
    {printf("Your dating range is %d to %d years old.\n",x/2+7,x*2-14);}
    else 
    {printf("You are too young to be dating.\n");}
    return 0;
}
