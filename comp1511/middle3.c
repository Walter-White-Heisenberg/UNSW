#include<stdio.h>
int main(void)
{int x,y,z;
    printf("Enter integer:");
    scanf("%d",&x);
    printf("Enter integer:");
    scanf("%d",&y);
    printf("Enter integer:");
    scanf("%d",&z);
    printf("Middle: %d\n",(x<=y)*(y<=z)*y+y*(z<y)*(y<=x)+x*(y<x)*(x<=z)+x*(z<x)*(x<y)+z*(x<z)*(z<y)+z*(y<z)*(z<x));
return 0;
}
