#include<stdio.h>

int main(void) {
    int x;
    int y;
    int z;
    
    printf("Enter integer: ");
    scanf("%d",&card_a);
    
    printf("Enter integer: ");
    scanf("%d",&y);
    
    printf("Enter integer: ");
    scanf("%d",&z);
    
    printf("The integers in order are: %d %d %d\n",x*(x<=y)*(x<=z)+y*(y<z)*(y<x)+z*(z<x)*(z<y),x+y+z-(x*(x>=y)*(x>=z)+y*(y>z)*(y>x)+z*(z>x)*(z>y))-(x*(x<=y)*(x<=z)+y*(y<z)*(y<x)+z*(z<x)*(z<y)),x*(x>=y)*(x>=z)+y*(y>z)*(y>x)+z*(z>x)*(z>y));
    
    return 0;
}
