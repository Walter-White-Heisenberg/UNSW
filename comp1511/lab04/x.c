#include<stdio.h>
int main(void)
{
int n,i;
i=1;
    printf("Enter size: ");
    scanf("%d",&n);
    while(i<=n)
    {   
    int x=0;
    int y=0;
        while(x<=n&&y<n){y++;
            x++;
            if( x==i || x==n-i+1 )
                {printf("*");}
            else{printf("-");}
        }
    i++;
    printf("\n");    
    }
return 0; 
}
