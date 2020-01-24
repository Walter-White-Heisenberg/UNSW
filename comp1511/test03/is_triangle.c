#include<stdio.h>
int main(void)
{
    double x,y,z,largest,rest;
    printf("Please enter three numbers: ");
    scanf("%lf %lf %lf",&x,&y,&z);
    largest=x*(x>=y)*(x>=z)+y*(y>x)*(y>=z)+z*(z>y)*(z>x);
    rest=x+y+z-largest;
    if(rest>largest)
    {
        printf("triangle\n");
    }
    else 
    {
        printf("not a triangle\n");
    }    
    return 0;
}
