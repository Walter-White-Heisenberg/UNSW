#include<stdio.h>
int main(void)
{
    int x,y;
    int z;
    scanf("%d%d",&x,&y);
    z=x-y;
    if (z<0)
    {
        printf("%d\n",-z);
    }
    else if (z>0)
    {
        printf("%d\n",z);
    } 
    else{printf("equal\n");}
    return 0;   
}
