#include<stdio.h>
int main(void){
    printf("Enter integer:");
    int x; 
    scanf("%d",&x);sd
    printf("Enter integer:");
    int y; 
    scanf("%d",&y);
    printf("Enter integer:");
    int z; 
    scanf("%d",&z);
    printf("The integers in order are: %d %d %d\n",x*(x<=y)*(x<=z)+y*(y<x)*(y<=z)+z*(z<x)*(z<y),x+y+z-(x*(x<=y)*(x<=z)+y*(y<x)*(y<=z)+z*(z<x)*(z<y))-(x*(x>=y)*(x>=z)+y*(y>x)*(y>=z)+z*(z>x)*(z>y)),x*(x>=y)*(x>=z)+y*(y>x)*(y>=z)+z*(z>x)*(z>y));
    return 0;
}
